/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** map_content.c
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server_handler.h"
#include "commands.h"

static void write_tile_resource(server_handler_t *server, map_t *tile,
    const int idx)
{
    write(server->game_data.clients[idx].fd,
        tile->ressources.food_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd,
        tile->ressources.linemate_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd,
        tile->ressources.deraumere_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd,
        tile->ressources.sibur_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd,
        tile->ressources.mendiane_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd,
        tile->ressources.phiras_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd,
        tile->ressources.thystame_nb, sizeof(int));
}

map_t *get_tile_content(server_handler_t *server, int x, int y)
{
    map_t *tile = malloc(sizeof(map_t));

    if (tile == NULL)
        return (NULL);
    memcpy(tile, &server->game_data.map[x][y], sizeof(map_t));
    return (tile);
}

int tile_content_request(server_handler_t *server, char **args, const int idx)
{
    int x = atoi(args[1]);
    int y = atoi(args[2]);
    map_t *tile = get_tile_content(server, x, y);

    if (tile == NULL)
        return (EXIT_FAILURE);
    write(server->game_data.clients[idx].fd, TILE_CONTENT_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd, args[1], strlen(args[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write(server->game_data.clients[idx].fd, args[2], strlen(args[2]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER, 1));
    write_map_resource(server, x, y, idx)
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR, 1));
    free(tile);
    return (EXIT_SUCCESS);
}

static int get_y_tiles(server_handler_t *server, char **tile_command,
    const int idx)
{
    for (int j = 0; j < server->game_data.map_size[1]; ++j) {
            if (asprintf(&tile_command[2], "%d", j) == -1)
                return (EXIT_FAILURE);
            if (tile_content_request(server, tile_command, idx)
                == EXIT_FAILURE) {
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
    for (int i = 0; i < server->game_data.map_size[0]; ++i) {
        if (asprintf(&tile_command[1], "%d", i) == -1)
            return (EXIT_FAILURE);
        if (get_y_tiles(server, tile_command, idx) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        free(tile_command[1]);
    }
    return (EXIT_SUCCESS);
}

int map_content_request(server_handler_t *server, char **args, const int idx)
{
    char **tile_command = malloc(sizeof(char *) * 4);

    (void) args;
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
