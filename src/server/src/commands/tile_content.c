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
    memcpy(tile, &server->game_data.map[x][y], sizeof(map_t));
    return (tile);
}
