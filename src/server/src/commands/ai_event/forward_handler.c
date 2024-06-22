/*
** EPITECH PROJECT, 2024
** server
** File description:
** forward_handler
*/

#include "show.h"
#include "utils.h"
#include "ai_event.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

void do_forward(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);

    go_in_good_direction(&server->game_data, idx,
    &server->game_data.clients[idx].pos[0],
    &server->game_data.clients[idx].pos[1]);
    write_to_client(event.fd, ALL_FINE);
}

int add_forward(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

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
