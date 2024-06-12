/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** show_game_data
*/

#include <stdio.h>
#include <string.h>

#include "show.h"

static void show_tile_content(server_handler_t *server, const int y,
    const int x)
{
    printf("\tx = %d, y = %d: ", x, y);
    printf("\t[player_nb: %d, "
    "food: %d, "
    "linemate: %d, "
    "deraumere: %d, "
    "sibur: %d, "
    "mendiane: %d, "
    "phiras: %d, "
    "thystame: %d]\n",
    server->game_data.map[y][x].player_nb,
    server->game_data.map[y][x].ressources.food_nb,
    server->game_data.map[y][x].ressources.linemate_nb,
    server->game_data.map[y][x].ressources.deraumere_nb,
    server->game_data.map[y][x].ressources.sibur_nb,
    server->game_data.map[y][x].ressources.mendiane_nb,
    server->game_data.map[y][x].ressources.phiras_nb,
    server->game_data.map[y][x].ressources.thystame_nb);
}

static void show_map_content(server_handler_t *server)
{
    printf("Map content:\n");
    for (int y = 0; y < server->game_data.map_size[1]; y++) {
        printf("[\n");
        for (int x = 0; x < server->game_data.map_size[0]; x++) {
            show_tile_content(server, y, x);
        }
        printf("]\n");
    }
}

static void show_single_client_data(server_handler_t *server, const int i)
{
    printf("\tClient num %d:\n", server->game_data.clients[i].client_num);
    printf("\t\t- Fd: %d\n"
    "\t\t- Is_connected: %d\n"
    "\t\t- Team name: %s\n"
    "\t\t- Level: %d\n"
    "\t\t- x: %d, y: %d\n"
    "\t\t- Time life: %d\n"
    "\t\t- Direction: %d\n",
    server->game_data.clients[i].fd,
    server->game_data.clients[i].is_connected,
    server->game_data.clients[i].team_name,
    server->game_data.clients[i].level,
    server->game_data.clients[i].pos[0],
    server->game_data.clients[i].pos[1],
    server->game_data.clients[i].time_life,
    server->game_data.clients[i].direction);
}

static void show_clients_data(server_handler_t *server)
{
    printf("Clients data:\n");
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].client_num == UNKNOWN ||
        server->game_data.clients[i].team_name == NULL ||
        strcmp(server->game_data.clients[i].team_name, "GRAPHIC") == 0) {
            continue;
        }
        show_single_client_data(server, i);
    }
    printf("\n");
}

static void show_teams_data(server_handler_t *server)
{
    printf("Teams data:\n");
    for (int i = 0; server->game_data.teams[i].team_name != NULL; i++) {
        printf("\t- Team %d:\n", (i + 1));
        printf("\t\tTeam name: %s\n", server->game_data.teams[i].team_name);
        printf("\t\tNumber of clients: %d\n",
        server->game_data.teams[i].client_total);
        printf("\t\tNumber of each client:\n");
        for (int x = 0;
        server->game_data.teams[i].client_num_list[x] != UNKNOWN; x++) {
            printf("\t\t\t- %d\n",
            server->game_data.teams[i].client_num_list[x]);
        }
    }
    printf("\n");
}

static void show_ressources_in_map(server_handler_t *server)
{
    printf("Ressources in the map:\n"
    "\t- Food: %d\n"
    "\t- Linemate: %d\n"
    "\t- Deraumere: %d\n"
    "\t- Sibur: %d\n"
    "\t- Mendiane: %d\n"
    "\t- Phiras: %d\n"
    "\t- Thystame: %d\n\n",
    server->game_data.total_ressources.food_nb,
    server->game_data.total_ressources.linemate_nb,
    server->game_data.total_ressources.deraumere_nb,
    server->game_data.total_ressources.sibur_nb,
    server->game_data.total_ressources.mendiane_nb,
    server->game_data.total_ressources.phiras_nb,
    server->game_data.total_ressources.thystame_nb);
}

static void show_ressources_quantity(server_handler_t *server)
{
    printf("Ressources quantity:\n"
    "\t- Food: %d\n"
    "\t- Linemate: %d\n"
    "\t- Deraumere: %d\n"
    "\t- Sibur: %d\n"
    "\t- Mendiane: %d\n"
    "\t- Phiras: %d\n"
    "\t- Thystame: %d\n\n",
    server->game_data.ressources_quantity.food_nb,
    server->game_data.ressources_quantity.linemate_nb,
    server->game_data.ressources_quantity.deraumere_nb,
    server->game_data.ressources_quantity.sibur_nb,
    server->game_data.ressources_quantity.mendiane_nb,
    server->game_data.ressources_quantity.phiras_nb,
    server->game_data.ressources_quantity.thystame_nb);
}

int show_game_data(server_handler_t *server, bool need_to_show)
{
    if (need_to_show == false) {
        return (0);
    }
    printf("Map x size: %d, map y size: %d\n\n", server->game_data.map_size[0],
    server->game_data.map_size[1]);
    printf("Frequence: %d\n\n", server->game_data.frequence);
    show_ressources_quantity(server);
    show_ressources_in_map(server);
    show_teams_data(server);
    show_clients_data(server);
    show_map_content(server);
    return (0);
}
