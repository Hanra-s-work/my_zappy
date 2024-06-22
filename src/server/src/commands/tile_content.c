/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** tile_content.c
*/

#include <string.h>

#include "server_handler.h"

map_t *get_tile_content(server_handler_t *server, int x, int y)
{
    map_t *tile = malloc(sizeof(map_t));

    if (tile == NULL)
        return (NULL);
    if (x < 0 || x > server->game_data.map_size[0] || y < 0 ||
    y > server->game_data.map_size[1])
        return (NULL);
    memcpy(tile, &server->game_data.map[y][x], sizeof(map_t));
    return (tile);
}
