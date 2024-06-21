/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** incantation_sender
*/

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "ai_event.h"
#include "server_handler.h"

static char *fill_one(game_data_t game, const int *indexes, const int idx,
    const int x)
{
    char *str = NULL;

    if (x == 1) {
        str = malloc(sizeof(char) * MAX_BUFFER_SIZE);
        if (str == NULL) {
            return (NULL);
        }
        sprintf(str, "pic %d %d %d #%d #%d\n",
        game.map_size[0], game.map_size[1],
        game.clients[idx].level, game.clients[idx].client_num,
        game.clients[indexes[0]].client_num);
    }
    return (str);
}

static char *fill_three(game_data_t game, const int *indexes, const int idx,
    const int x)
{
    char *str = NULL;

    if (x == 3) {
        str = malloc(sizeof(char) * MAX_BUFFER_SIZE);
        if (str == NULL) {
            return (NULL);
        }
        sprintf(str, "pic %d %d %d #%d #%d #%d #%d\n",
        game.map_size[0], game.map_size[1],
        game.clients[idx].level, game.clients[idx].client_num,
        game.clients[indexes[0]].client_num,
        game.clients[indexes[1]].client_num,
        game.clients[indexes[2]].client_num);
    }
    return (str);
}

static char *fill_five(game_data_t game, const int *indexes, const int idx,
    const int x)
{
    char *str = NULL;

    if (x == 5) {
        str = malloc(sizeof(char) * MAX_BUFFER_SIZE);
        if (str == NULL) {
            return (NULL);
        }
        sprintf(str, "pic %d %d %d #%d #%d #%d #%d #%d #%d\n",
        game.map_size[0], game.map_size[1],
        game.clients[idx].level, game.clients[idx].client_num,
        game.clients[indexes[0]].client_num,
        game.clients[indexes[1]].client_num,
        game.clients[indexes[2]].client_num,
        game.clients[indexes[3]].client_num,
        game.clients[indexes[4]].client_num);
    }
    return (str);
}

static char *fill_str(game_data_t game, const int *indexes, const int idx,
    const int x)
{
    char *str = NULL;

    if (x == 0) {
        str = malloc(sizeof(char) * MAX_BUFFER_SIZE);
        if (str == NULL)
            return (NULL);
        sprintf(str, "pic %d %d %d #%d\n",
        game.map_size[0], game.map_size[1],
        game.clients[idx].level, game.clients[idx].client_num);
    }
    if (str == NULL) {
        fill_one(game, indexes, idx, x);
    }
    if (str == NULL) {
        fill_three(game, indexes, idx, x);
    }
    if (str == NULL) {
        fill_five(game, indexes, idx, x);
    }
    return (str);
}

static void send_start(game_data_t game, const int *indexes, const int idx)
{
    char *str = NULL;
    int x = 0;

    write_to_client(game.clients[idx].fd, ELEVATION_UNDERWAY);
    if (indexes != NULL) {
        for (; indexes[x] != -1; x++)
            write_to_client(game.clients[indexes[x]].fd, ELEVATION_UNDERWAY);
    }
    str = fill_str(game, indexes, idx, x);
    if (str == NULL) {
        return;
    }
    write_to_graphics_clients(game.clients, str);
    free(str);
}

static void remove_ressources_lvl_7(game_data_t *game, const int idx,
    const int *player_pos)
{
    if (game->clients[idx].level == 7) {
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.deraumere_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.mendiane_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.phiras_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.thystame_nb--;
    }
}

static void remove_ressources_2(game_data_t *game, const int idx,
    const int *player_pos)
{
    if (game->clients[idx].level == 4) {
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.deraumere_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.phiras_nb--;
    }
    if (game->clients[idx].level == 5) {
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.deraumere_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.mendiane_nb -= 3;
    }
    if (game->clients[idx].level == 6) {
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.deraumere_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb -= 3;
        game->map[player_pos[1]][player_pos[0]].ressources.phiras_nb--;
    }
    remove_ressources_lvl_7(game, idx, player_pos);
}

static void remove_ressources(game_data_t *game, const int idx)
{
    int *player_pos = game->clients[idx].pos;

    if (game->clients[idx].level == 1)
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb--;
    if (game->clients[idx].level == 2) {
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.deraumere_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb--;
    }
    if (game->clients[idx].level == 3) {
        game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb -= 2;
        game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb--;
        game->map[player_pos[1]][player_pos[0]].ressources.phiras_nb -= 2;
    }
    remove_ressources_2(game, idx, player_pos);
}

static void send_end(game_data_t *game, const int *indexes, const int idx)
{
    char str[MAX_BUFFER_SIZE];

    remove_ressources(game, idx);
    game->clients[idx].level++;
    sprintf(str, "Current level: %d\n", game->clients[idx].level);
    write_to_client(game->clients[idx].fd, str);
    if (indexes != NULL) {
        for (int i = 0; indexes[i] != -1; i++) {
            game->clients[indexes[i]].level++;
            write_to_client(game->clients[indexes[i]].fd, str);
        }
    }
    sprintf(str, "pie %d %d 1\n", game->clients[idx].pos[0],
    game->clients[idx].pos[1]);
    write_to_graphics_clients(game->clients, str);
}

int send_success(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    if (is_start == true) {
        send_start(*game, game->event[i].indexes, idx);
    } else {
        send_end(game, game->event[i].indexes, idx);
    }
    return (0);
}
