/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** map_content.c
*/

#include <unistd.h>

#include "commands.h"

int command_parameter_error(server_handler_t *server, char **args, const int
    idx)
{
    (void) args;
    write(server->game_data.clients[idx].fd, COMMAND_PARAMETER_ERROR,
            COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR, 1);
    return (0);
}
