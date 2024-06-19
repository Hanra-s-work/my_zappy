/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** connect_handler
*/

#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"

int do_connect(server_handler_t *server, char **parsed_command,
    const int idx)
{
    char *str = NULL;
    int nbr = 0;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].team_name == NULL || i == idx) {
            continue;
        }
        if (strcmp(server->game_data.clients[i].team_name,
        server->game_data.clients[idx].team_name) == 0) {
            nbr++;
        }
    }
    sprintf(str, "%d\n", nbr);
    write_to_client(server->game_data.clients[idx].fd, str);
    return (0);
}
