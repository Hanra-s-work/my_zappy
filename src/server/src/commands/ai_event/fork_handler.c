/*
** EPITECH PROJECT, 2024
** server
** File description:
** fork_handler
*/

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"

static void send_to_gui_fork_started(server_handler_t *server,
    const cli_t client)
{
    char str[MAX_BUFFER_SIZE];

    sprintf(str, "pfk #%d\n", client.client_num);
    write_to_graphics_clients(server->game_data.clients, str);
}

int add_fork(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 0;

    if (get_array_len(parsed_command) != 1)
        return (-1);
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = FORK;
            server->game_data.event[i].time_counter = FORK_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[FORK - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL) {
        send_to_gui_fork_started(server, server->game_data.clients[idx]);
        return (0);
    }
    delete_event(&server->game_data.event[i]);
    return (-1);
}
