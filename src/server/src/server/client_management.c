/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** client_management
*/

#include <unistd.h>

#include "ai_event.h"
#include "server_handler.h"

void init_client(cli_t client[MAX_CLIENT])
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        client[i] = DEFAULT_CLIENT;
    }
}

int get_client(cli_t client[MAX_CLIENT], const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].fd == fd) {
            return (i);
        }
    }
    return (-1);
}

int delete_client(server_handler_t *server, const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].fd != fd) {
            continue;
        }
        close(server->game_data.clients[i].fd);
        if (server->game_data.clients[i].team_name != NULL) {
            free(server->game_data.clients[i].team_name);
        }
        delete_client_current_event(server, server->game_data.clients[i].fd);
        server->game_data.clients[i] = DEFAULT_CLIENT;
        return (0);
    }
    return (-1);
}

void delete_all_client(cli_t client[MAX_CLIENT])
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].fd != UNKNOWN) {
            close(client[i].fd);
        }
        if (client[i].team_name != NULL) {
            free(client[i].team_name);
        }
        client[i] = DEFAULT_CLIENT;
    }
}
