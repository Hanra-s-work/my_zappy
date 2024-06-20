/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** broadcast_handler
*/

#include <string.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

void do_broadcast(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);

    write_to_client(event.fd, ALL_FINE);
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (i == idx || server->game_data.clients[i].team_name == NULL ||
        strcmp(server->game_data.clients[i].team_name, GUI_TEAM_NAME) == 0) {
            continue;
        }
        write_to_client(server->game_data.clients[i].fd, ALL_FINE);
    }
}

int add_broadcast(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 0;

    if (get_array_len(parsed_command) != 2) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = BROADCAST;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[BROADCAST - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
