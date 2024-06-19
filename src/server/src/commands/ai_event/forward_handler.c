/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward_handler
*/

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"

int add_forward(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 0;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = FORWARD;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[FORWARD - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
