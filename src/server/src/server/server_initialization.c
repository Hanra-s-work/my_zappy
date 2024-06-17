/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** server_initialization
*/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "utils.h"
#include "server_handler.h"

static int bind_server(server_handler_t *server, char *value)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(value));
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server->socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return (-1);
    }
    return (0);
}

static int init_server_queue(server_handler_t *server)
{
    if (listen(server->socket, MAX_CLIENT) == -1) {
        perror("listen");
        return (-1);
    }
    return (0);
}

int server_initialization(server_handler_t *server, struct arg_s **arguments)
{
    char *value = NULL;

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        perror("socket");
        return (-1);
    }
    value = (char *)find_value_by_param((const struct arg_s **)arguments,
        "-p");
    if (bind_server(server, value) == -1) {
        return (-1);
    }
    if (init_server_queue(server) == -1) {
        return (-1);
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        server->fd_queue[i] = UNKNOWN;
    }
    return init_game_data(server, arguments);
}
