/*
** EPITECH PROJECT, 2024
** server
** File description:
** inventory_handler
*/

#include <stdio.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

void do_inventory(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    char str[MAX_BUFFER_SIZE];

    sprintf(str, "[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, "
    "phiras %d, thystame %d]\n",
    server->game_data.clients[idx].ressources.food_nb,
    server->game_data.clients[idx].ressources.linemate_nb,
    server->game_data.clients[idx].ressources.deraumere_nb,
    server->game_data.clients[idx].ressources.sibur_nb,
    server->game_data.clients[idx].ressources.mendiane_nb,
    server->game_data.clients[idx].ressources.phiras_nb,
    server->game_data.clients[idx].ressources.thystame_nb);
    write_to_client(event.fd, str);
}

int add_inventory(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = INVENTORY;
            server->game_data.event[i].time_counter = INVENTORY_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[INVENTORY - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
