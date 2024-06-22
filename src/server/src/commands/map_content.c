/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** map_content.c
*/

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"
#include "commands.h"
#include "server_handler.h"

static void write_tile_to_client(server_handler_t *server, const int idx,
    char **to_str)
{
    write(server->game_data.clients[idx].fd, to_str[0], strlen(to_str[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[1], strlen(to_str[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[2], strlen(to_str[2]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[3], strlen(to_str[3]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[4], strlen(to_str[4]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[5], strlen(to_str[5]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[6], strlen(to_str[6]));
}

static void get_tile_resource(server_handler_t *server, map_t *tile,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 7);

    if (int_to_str_data == NULL)
        return;
    asprintf(&int_to_str_data[0], "%d", tile->ressources.food_nb);
    asprintf(&int_to_str_data[1], "%d", tile->ressources.linemate_nb);
    asprintf(&int_to_str_data[2], "%d", tile->ressources.deraumere_nb);
    asprintf(&int_to_str_data[3], "%d", tile->ressources.sibur_nb);
    asprintf(&int_to_str_data[4], "%d", tile->ressources.mendiane_nb);
    asprintf(&int_to_str_data[5], "%d", tile->ressources.phiras_nb);
    asprintf(&int_to_str_data[6], "%d", tile->ressources.thystame_nb);
    write_tile_to_client(server, idx, int_to_str_data);
    free_array_size_n(int_to_str_data, 7);
}

static void write_tile_request(server_handler_t *server, char **args,
    const int idx, map_t *tile)
{
    write(server->game_data.clients[idx].fd, TILE_CONTENT_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, args[1], strlen(args[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, args[2], strlen(args[2]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    get_tile_resource(server, tile, idx);
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
}

int tile_content_request(server_handler_t *server, char **args, const int idx)
{
    int x = 0;
    int y = 0;
    map_t *tile = NULL;

    if (get_array_len(args) != 3)
        return (command_parameter_error(server, idx));
    x = atoi(args[1]);
    y = atoi(args[2]);
    tile = get_tile_content(server, x, y);
    if (tile == NULL)
        return (EXIT_FAILURE);
    write_tile_request(server, args, idx, tile);
    free(tile);
    return (EXIT_SUCCESS);
}

static int get_x_tiles(server_handler_t *server, char **tile_command,
    const int idx)
{
    for (int j = 0; j < server->game_data.map_size[0]; ++j) {
        if (asprintf(&tile_command[2], "%d", j) == -1)
            return (EXIT_FAILURE);
        if (tile_content_request(server, tile_command, idx) == EXIT_FAILURE) {
            free(tile_command[2]);
            return (EXIT_FAILURE);
        }
        free(tile_command[2]);
    }
    return (EXIT_SUCCESS);
}

static int get_all_tiles(server_handler_t *server, char **tile_command,
    const int idx)
{
    for (int i = 0; i < server->game_data.map_size[1]; ++i) {
        if (asprintf(&tile_command[1], "%d", i) == -1)
            return (EXIT_FAILURE);
        if (get_x_tiles(server, tile_command, idx) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        free(tile_command[1]);
    }
    return (EXIT_SUCCESS);
}

int map_content_request(server_handler_t *server, char **args, const int idx)
{
    char **tile_command = NULL;

    if (get_array_len(args) != 1)
        return (command_parameter_error(server, idx));
    tile_command = malloc(sizeof(char *) * 4);
    if (tile_command == NULL)
        return (EXIT_FAILURE);
    tile_command[0] = strdup(TILE_CONTENT_COMMAND);
    if (tile_command[0] == NULL)
        return (EXIT_FAILURE);
    tile_command[3] = NULL;
    get_all_tiles(server, tile_command, idx);
    free(tile_command[0]);
    free(tile_command);
    return (EXIT_SUCCESS);
}
