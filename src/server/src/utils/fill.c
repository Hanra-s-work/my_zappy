/*
** EPITECH PROJECT, 2024
** server
** File description:
** randomizer
*/

#include "server_handler.h"

static void check_which_type(game_data_t *game_data, ressources_type_t type,
    const int x, const int y)
{
    if (type == FOOD)
        game_data->map[y][x].ressources.food_nb++;
    if (type == LINEMATE)
        game_data->map[y][x].ressources.linemate_nb++;
    if (type == DERAUMERE)
        game_data->map[y][x].ressources.deraumere_nb++;
    if (type == SIBUR)
        game_data->map[y][x].ressources.sibur_nb++;
    if (type == MENDIANE)
        game_data->map[y][x].ressources.mendiane_nb++;
    if (type == PHIRAS)
        game_data->map[y][x].ressources.phiras_nb++;
    if (type == THYSTAME)
        game_data->map[y][x].ressources.thystame_nb++;
}

static void randomize_map_content(game_data_t *game_data, int *value,
    const int total, ressources_type_t type)
{
    int x = game_data->map_size[0];
    int y = game_data->map_size[1];
    int ressource_x = 0;
    int ressource_y = 0;

    while (*value < total) {
        ressource_x = rand() % x;
        ressource_y = rand() % y;
        check_which_type(game_data, type, ressource_x, ressource_y);
        (*value)++;
    }
}

static void call_randomizer(game_data_t *data)
{
    randomize_map_content(data, &data->total_ressources.food_nb,
    data->ressources_quantity.food_nb, FOOD);
    randomize_map_content(data, &data->total_ressources.linemate_nb,
    data->ressources_quantity.linemate_nb, LINEMATE);
    randomize_map_content(data, &data->total_ressources.deraumere_nb,
    data->ressources_quantity.deraumere_nb, DERAUMERE);
    randomize_map_content(data, &data->total_ressources.mendiane_nb,
    data->ressources_quantity.mendiane_nb, MENDIANE);
    randomize_map_content(data, &data->total_ressources.phiras_nb,
    data->ressources_quantity.phiras_nb, PHIRAS);
    randomize_map_content(data, &data->total_ressources.sibur_nb,
    data->ressources_quantity.sibur_nb, SIBUR);
    randomize_map_content(data, &data->total_ressources.thystame_nb,
    data->ressources_quantity.thystame_nb, THYSTAME);
}

void refill_map(game_data_t *game_data)
{
    call_randomizer(game_data);
}

void fill_map(server_handler_t *server)
{
    int player_x = 0;
    int player_y = 0;

    for (int a = 0; server->game_data.clients[a].client_num != UNKNOWN; a++) {
        player_x = server->game_data.clients[a].pos[0];
        player_y = server->game_data.clients[a].pos[1];
        server->game_data.map[player_y][player_x].player_nb++;
    }
    call_randomizer(&server->game_data);
}
