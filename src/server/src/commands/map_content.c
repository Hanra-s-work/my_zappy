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

static void get_tile(server_handler_t *server, char to_str[MAX_BUFFER_SIZE],
    const int x, const int y)
{
    memset(to_str, '\0', MAX_BUFFER_SIZE);
    sprintf(to_str, "%d %d %d %d %d %d %d %d %d %d\n",
    x, y, server->game_data.map[y][x].ressources.food_nb,
    server->game_data.map[y][x].ressources.food_nb,
    server->game_data.map[y][x].ressources.linemate_nb,
    server->game_data.map[y][x].ressources.deraumere_nb,
    server->game_data.map[y][x].ressources.sibur_nb,
    server->game_data.map[y][x].ressources.mendiane_nb,
    server->game_data.map[y][x].ressources.phiras_nb,
    server->game_data.map[y][x].ressources.thystame_nb);
}

static void update_values(server_handler_t *server, int *x, int *y)
{
    (*x)++;
    if (*x == server->game_data.map_size[0]) {
        *x = 0;
        (*y)++;
    }
}

int map_content_request(server_handler_t *server, char **args, const int idx)
{
    char str[MAP_BUFFER_SIZE];
    char to_str[MAX_BUFFER_SIZE];
    int x = 0;
    int y = 0;

    if (get_array_len(args) != 1)
        return (command_parameter_error(server, idx));
    memset(str, '\0', MAP_BUFFER_SIZE);
    for (int i = 0; i < server->game_data.map_size[0] *
    server->game_data.map_size[1]; i++) {
        strcat(str, "bct ");
        get_tile(server, to_str, x, y);
        strcat(str, to_str);
        update_values(server, &x, &y);
    }
    write_to_client(server->game_data.clients[idx].fd, str);
    return (0);
}
