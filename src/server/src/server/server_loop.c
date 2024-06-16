/*
** EPITECH PROJECT, 2024
** server
** File description:
** server_loop
*/

#include <arpa/inet.h>
#include <stdio.h>

#include "utils.h"
#include "constants.h"
#include "server_handler.h"

static void add_in_fd_queue(server_handler_t *server, const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->fd_queue[i] == UNKNOWN) {
            server->fd_queue[i] = fd;
            break;
        }
    }
}

static int connection_handling(server_handler_t *server, const int i)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int client_fd = 0;

    if (i == server->socket) {
        client_fd = accept(server->socket, (struct sockaddr *)&addr, &len);
        if (client_fd == -1) {
            return (write_error_msg(CONNEXION_FAILED));
        }
        FD_SET(client_fd, &server->current_fd);
        write_to_client(client_fd, "WELCOME\n");
        add_in_fd_queue(server, client_fd);
        printf("Connexion from %s:%d\n", inet_ntoa(addr.sin_addr),
        ntohs(addr.sin_port));
        return (0);
    }
    command_handling(server, i);
    return (0);
}

static int fd_loop_statement(server_handler_t *server, const int i)
{
    if (FD_ISSET(i, &server->ready_fd)) {
        if (connection_handling(server, i) == -1) {
            return (-1);
        }
    }
    return (0);
}

static int loop_in_fd(server_handler_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (fd_loop_statement(server, i) == -1) {
            return (-1);
        }
    }
    return (0);
}

void server_loop(server_handler_t *server)
{
    FD_ZERO(&server->current_fd);
    FD_SET(server->socket, &server->current_fd);
    while (true) {
        server->ready_fd = server->current_fd;
        if (select(FD_SETSIZE, &server->ready_fd, NULL, NULL, NULL) == -1) {
            break;
        }
        if (loop_in_fd(server) == -1) {
            break;
        }
    }
}