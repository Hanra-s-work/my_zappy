/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** commands.h
*/

#ifndef MY_ZAPPY_COMMANDS_H
    #define MY_ZAPPY_COMMANDS_H

    #include "server_handler.h"

    #define COMMAND_ID_LEN          3
    #define MAP_SIZE_COMMMAND       "msz"
    #define TEAM_NAME_COMMAND       "tna"
    #define TILE_CONTENT_COMMAND    "bct"
    #define TIME_UNIT_COMMAND       "sgt"
    #define COMMAND_PARAMETER_ERROR "sbp"

int map_size_request(server_handler_t *server, char **args, const int idx);

int all_team_name_request(server_handler_t *server, char **args, const int idx);

int time_unit_request(server_handler_t *server, char **args, const int idx);

int time_unit_modification_request(server_handler_t *server, char **args,
    const int idx);


int map_content_request(server_handler_t *server, char **args, const int idx);

int tile_content_request(server_handler_t *server, char **args, const int idx);


map_t *get_tile_content(server_handler_t *server, int x, int y);


int command_parameter_error(server_handler_t *server, char **args, const int
    idx);

#endif //MY_ZAPPY_COMMANDS_H