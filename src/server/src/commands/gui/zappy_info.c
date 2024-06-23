/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** zappy_info.c
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"
#include "command_parse.h"
#include "commands.h"
#include "server_handler.h"

int map_size_request(server_handler_t *server, char **args, const int idx)
{
    char *x;
    char *y;

    if (get_array_len(args) != 1) {
        return (command_parameter_error(server, idx));
    }
    asprintf(&x, "%d", server->game_data.map_size[0]);
    asprintf(&y, "%d", server->game_data.map_size[1]);
    if (x == NULL || y == NULL)
        return (EXIT_FAILURE);
    write(server->game_data.clients[idx].fd, MAP_SIZE_COMMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, x, strlen(x));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, y, strlen(y));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
    free(x);
    free(y);
    return (EXIT_SUCCESS);
}

int all_team_name_request(server_handler_t *server, char **args, const int idx)
{
    char str[MAX_BUFFER_SIZE];

    str[0] = '\0';
    if (get_array_len(args) != 1) {
        return (command_parameter_error(server, idx));
    }
    for (int i = 0; server->game_data.teams[i].team_name != NULL; ++i) {
        strcat(str, ALL_TEAM_COMMAND);
        strcat(str, COMMAND_DELIMITER_STR);
        strcat(str, server->game_data.teams[i].team_name);
        strcat(str, COMMAND_SEPARATOR_STR);
    }
    write_to_client(server->game_data.clients[idx].fd, str);
    return (EXIT_SUCCESS);
}

int time_unit_request(server_handler_t *server, char **args, const int idx)
{
    char *str_frequence;

    if (get_array_len(args) != 1) {
        return (command_parameter_error(server, idx));
    }
    if (asprintf(&str_frequence, "%d", server->game_data.frequence) == -1)
        return (EXIT_FAILURE);
    write(server->game_data.clients[idx].fd, TIME_UNIT_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, str_frequence,
        strlen(str_frequence));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
    free(str_frequence);
    return (EXIT_SUCCESS);
}

int time_unit_modification_request(server_handler_t *server, char **args,
    const int idx)
{
    int new_frequency = 0;

    if (get_array_len(args) != 2)
        return (command_parameter_error(server, idx));
    new_frequency = atoi(args[1]);
    if (new_frequency <= 0)
        return (command_parameter_error(server, idx));
    server->game_data.frequence = new_frequency;
    server->game_data.time = (double)1 / (double)server->game_data.frequence;
    server->game_data.time *= 1000000;
    write(server->game_data.clients[idx].fd, TIME_UNIT_MODIFICATION_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, args[1], strlen(args[1]));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
    return (EXIT_SUCCESS);
}
