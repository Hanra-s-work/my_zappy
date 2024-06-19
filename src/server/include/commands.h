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

int map_size_request(server_handler_t *server, char **args, const int idx);

int all_team_name_request(server_handler_t *server, char **args, const int idx);

int time_unit_request(server_handler_t *server, char **args, const int idx);

int time_unit_modification_request(server_handler_t *server, char **args,
    const int idx);


int map_content_request(server_handler_t *server, char **args, const int idx);

int tile_content_request(server_handler_t *server, char **args, const int idx);



#endif //MY_ZAPPY_COMMANDS_H
