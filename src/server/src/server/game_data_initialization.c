/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** game_data_initialization
*/

#include <string.h>

#include "show.h"
#include "utils.h"
#include "server_handler.h"
#include "client_management.h"

static void init_map_size(server_handler_t *server, struct arg_s **arguments)
{
    char *value = NULL;

    value = find_value_by_param((const struct arg_s **)arguments, "-x");
    server->game_data.map_size[0] = atoi(value);
    value = find_value_by_param((const struct arg_s **)arguments, "-y");
    server->game_data.map_size[1] = atoi(value);
}

static void init_ressources_quantity(server_handler_t *server)
{
    int basic = server->game_data.map_size[0] * server->game_data.map_size[1];
    int food = basic * FOOD_DENSITY;
    int linemate = basic * LINEMATE_DENSITY;
    int deraumere = basic * DERAUMERE_DENSITY;
    int sibur = basic * SIBUR_DENSITY;
    int mendiane = basic * MENDIANE_DENSITY;
    int phiras = basic * PHIRAS_DENSITY;
    int thystame = basic * THYSTAME_DENSITY;

    server->game_data.ressources_quantity.food_nb = food;
    server->game_data.ressources_quantity.linemate_nb = linemate;
    server->game_data.ressources_quantity.deraumere_nb = deraumere;
    server->game_data.ressources_quantity.sibur_nb = sibur;
    server->game_data.ressources_quantity.mendiane_nb = mendiane;
    server->game_data.ressources_quantity.phiras_nb = phiras;
    server->game_data.ressources_quantity.thystame_nb = thystame;
    server->game_data.total_ressources = DEFAULT_RESSOURCES;
}

static int search_unfilled_index(cli_t client[MAX_CLIENT])
{
    int index = 0;

    for (; client[index].client_num != UNKNOWN; index++);
    return index;
}

static bool check_if_already_taken_pos(cli_t clients[MAX_CLIENT], const int x,
    const int y)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (clients[i].pos[0] == x && clients[i].pos[1] == y) {
            return true;
        }
    }
    return false;
}

static void randomize_player_pos_and_dir(server_handler_t *server,
    const int index)
{
    int x = 0;
    int y = 0;
    int dir = 0;

    while (check_if_already_taken_pos(server->game_data.clients,
    x, y) == true) {
        for (int i = 0; i < 10; i++) {
            x = rand() % server->game_data.map_size[0];
            y = rand() % server->game_data.map_size[1];
            dir = rand() % 4;
        }
    }
    server->game_data.clients[index].pos[0] = x;
    server->game_data.clients[index].pos[1] = y;
    server->game_data.clients[index].direction = dir + 1;
}

static int init_player(server_handler_t *server, const int total, const int i)
{
    int index = 0;
    int time_life = PLAYER_TIME / server->game_data.frequence;

    for (int x = 0; x < MAX_CLIENT; x++) {
        server->game_data.teams[i].client_num_list[x] = UNKNOWN;
    }
    for (int nb = 0; nb < total; nb++) {
        server->game_data.teams[i].client_num_list[nb] = nb + 1;
        index = search_unfilled_index(server->game_data.clients);
        server->game_data.clients[index].client_num = nb + 1;
        server->game_data.clients[index].team_name =
        strdup(server->game_data.teams[i].team_name);
        if (server->game_data.clients[index].team_name == NULL) {
            return (-1);
        }
        server->game_data.clients[index].level = 1;
        server->game_data.clients[index].time_life = time_life;
        randomize_player_pos_and_dir(server, index);
    }
    return (0);
}

static int init_team_data(server_handler_t *server, struct arg_s **arguments)
{
    int index = find_index_by_param((const struct arg_s **)arguments, "-n");
    int nb_value = arguments[index]->nb_value;
    char **names = arguments[index]->value;
    char *value = find_value_by_param((const struct arg_s **)arguments, "-c");

    server->game_data.teams = malloc(sizeof(team_t) * (nb_value + 1));
    if (server->game_data.teams == NULL)
        return (-1);
    server->game_data.teams[nb_value].team_name = NULL;
    for (int i = 0; i < nb_value; i++) {
        server->game_data.teams[i].team_name = strdup(names[i]);
        if (server->game_data.teams[i].team_name == NULL)
            return (-1);
        server->game_data.teams[i].client_total = atoi(value);
        if (init_player(server,
        server->game_data.teams[i].client_total, i) == -1)
            return (-1);
    }
    return (0);
}

static int init_map_content(server_handler_t *server)
{
    int x = server->game_data.map_size[0];
    int y = server->game_data.map_size[1];

    server->game_data.map = malloc(sizeof(map_t *) * (y + 1));
    if (server->game_data.map == NULL) {
        return (-1);
    }
    server->game_data.map[y] = NULL;
    for (int j = 0; j < y; j++) {
        server->game_data.map[j] = malloc(sizeof(map_t) * x);
        if (server->game_data.map[j] == NULL) {
            return (-1);
        }
        for (int i = 0; i < x; i++) {
            server->game_data.map[j][i].player_nb = 0;
            server->game_data.map[j][i].ressources = DEFAULT_RESSOURCES;
        }
    }
    fill_map(server);
    return (0);
}

int init_game_data(server_handler_t *server, struct arg_s **arguments)
{
    char *value = find_value_by_param((const struct arg_s **)arguments, "-f");

    server->game_data.map = NULL;
    server->game_data.teams = NULL;
    if (value != NULL) {
        server->game_data.frequence = atoi(value);
    } else {
        server->game_data.frequence = DEFAULT_FREQUENCE;
    }
    init_client(server->game_data.clients);
    init_map_size(server, arguments);
    init_ressources_quantity(server);
    if (init_team_data(server, arguments) == -1) {
        return (write_error_msg("Error: Internal server error.\n"));
    }
    if (init_map_content(server) == -1) {
        return (write_error_msg("Error: Internal server error.\n"));
    }
    return (show_game_data(server, true));
}
