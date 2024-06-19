/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** zappy_info.c
*/

#include <unistd.h>
#include "server_handler.h"
#include "commands.h"

int map_size_request(server_handler_t *server, char **args, const int idx)
{
    (void) args;

    write(server->game_data.clients[idx].fd, MAP_SIZE_COMMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1);
    write(server->game_data.clients[idx].fd, server->game_data.map_size[0],
        sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1);
    write(server->game_data.clients[idx].fd, server->game_data.map_size[1],
        sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR, 1);
    return (EXIT_SUCCESS);
}

int all_team_name_request(server_handler_t *server, char **args, const int idx)
{
    (void) args;
    return (EXIT_SUCCESS);
}

int time_unit_request(server_handler_t *server, char **args, const int idx)
{
    return (EXIT_SUCCESS);
}

int time_unit_modification_request(server_handler_t *server, char **args,
    const int idx)
{
    return (EXIT_SUCCESS);
}
