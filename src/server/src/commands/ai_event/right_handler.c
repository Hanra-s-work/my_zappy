/*
** EPITECH PROJECT, 2024
** server
** File description:
** right_handler
*/

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

void do_right(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    bool turned = false;

    if (server->game_data.clients[idx].direction == UP && turned == false) {
        server->game_data.clients[idx].direction = RIGHT;
        turned = true;
    }
    if (server->game_data.clients[idx].direction == LEFT && turned == false) {
        server->game_data.clients[idx].direction = UP;
        turned = true;
    }
    if (server->game_data.clients[idx].direction == DOWN && turned == false) {
        server->game_data.clients[idx].direction = LEFT;
        turned = true;
    }
    if (server->game_data.clients[idx].direction == RIGHT && turned == false) {
        server->game_data.clients[idx].direction = DOWN;
        turned = true;
    }
    write_to_client(event.fd, ALL_FINE);
}

int add_right(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = RIGHT_EVENT;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[RIGHT - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
