/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** zappy_info.c
*/

#include <unistd.h>
#include "server_handler.h"

int map_size_request(server_handler_t *server, char **args, const int idx)
{
    (void)args;
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
    write(server->game_data.clients[idx].fd, TIME_UNIT_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1);
    write(server->game_data.clients[idx].fd, server->game_data.frequence,
        sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR, 1);
    return (EXIT_SUCCESS);
}

int time_unit_modification_request(server_handler_t *server, char **args,
    const int idx)
{
    int new_frequency = atoi(args[1]);

    if (new_frequency <= 0) {
        command_parameter_error(server, args, idx);
        return (EXIT_SUCCESS);
    }
    server->game_data.frequence = new_frequency;
    write(server->game_data.clients[idx].fd, TIME_UNIT_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1);
    write(server->game_data.clients[idx].fd, new_frequency,
        sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR, 1);
    return (EXIT_SUCCESS);
}
