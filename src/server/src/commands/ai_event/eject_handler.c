/*
** EPITECH PROJECT, 2024
** server
** File description:
** eject_handler
*/

#include <stdio.h>

#include "utils.h"
#include "ai_event.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static void write_eject_to_gui(server_handler_t *server, const int num)
{
    char str[MAX_BUFFER_SIZE];

    sprintf(str, "pex #%d\n", num);
    write_to_graphics_clients(server->game_data.clients, str);
}

void do_eject(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    int *player_pos = server->game_data.clients[idx].pos;

    if (server->game_data.map[player_pos[1]][player_pos[0]].player_nb < 2) {
        write_to_client(event.fd, AI_COMMAND_FAILED);
        return;
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].pos[0] == player_pos[0] &&
        server->game_data.clients[i].pos[1] == player_pos[1]) {
            go_in_good_direction(&server->game_data, idx,
            &server->game_data.clients[i].pos[0],
            &server->game_data.clients[i].pos[1]);
        }
    }
    write_eject_to_gui(server, server->game_data.clients[idx].client_num);
}

int add_eject(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = EJECT;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[EJECT - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
