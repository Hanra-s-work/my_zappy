/*
** EPITECH PROJECT, 2024
** server
** File description:
** incantation_handler
*/

#include <stdio.h>

#include "utils.h"
#include "ai_event.h"
#include "command_parse.h"
#include "server_handler.h"

static int search_player(game_data_t *game, const int i, const int idx,
    const size_t size)
{
    int player_pos[2] = game->clients[idx].pos;
    int nb = 0;

    game->event[i].indexes = malloc(sizeof(int) * (size + 1));
    if (game->event[i].indexes == NULL)
        return (-1);
    game->event[i].indexes[size] = UNKNOWN;
    for (int i = 0; i < MAX_CLIENT && nb != size; i++) {
        if (i == idx)
            continue;
        if (game->clients[i].level == game->clients[idx].level &&
        game->clients[i].pos[0] == game->clients[idx].pos[0] &&
        game->clients[i].pos[1] == game->clients[idx].pos[1]) {
            game->event[i].indexes[nb] = i;
            nb++;
        }
    }
    if (nb != size)
        return (-1);
    return (0);
}

static int check_level_1(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    int player_pos[2] = game->clients[idx].pos;

    if (game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb < 1) {
        return (-1);
    }
    return (0);
}

static int check_level_2(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    int player_pos[2] = game->clients[idx].pos;

    if (game->map[player_pos[1]][player_pos[0]].player_nb < 2 ||
    game->map[player_pos[1]][player_pos[0]].ressources.linemate_nb < 1 ||
    game->map[player_pos[1]][player_pos[0]].ressources.deraumere_nb < 1 ||
    game->map[player_pos[1]][player_pos[0]].ressources.sibur_nb < 1)
        return (-1);
    if (search_player(game, i, idx, 1) == -1) {
        return (-1);
    }
    return (send_success(&game, i, idx, is_start));
}

static int check_level_3(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    return (0);
}

static int check_level_4(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    return (0);
}

static int check_level_5(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    return (0);
}

static int check_level_6(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    return (0);
}

static int check_level_7(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    return (0);
}

int check_incantation_condition(game_data_t *game, const int i, const int idx,
    const bool is_start)
{
    if (game->clients[idx].level == 1)
        return (check_level_1(game, i, idx, is_start));
    if (game->clients[idx].level == 2)
        return (check_level_2(game, i, idx, is_start));
    if (game->clients[idx].level == 3)
        return (check_level_3(game, i, idx, is_start));
    if (game->clients[idx].level == 4)
        return (check_level_4(game, i, idx, is_start));
    if (game->clients[idx].level == 5)
        return (check_level_5(game, i, idx, is_start));
    if (game->clients[idx].level == 6)
        return (check_level_6(game, i, idx, is_start));
    if (game->clients[idx].level == 7)
        return (check_level_7(game, i, idx, is_start));
    if (game->clients[idx].level > 7)
        return (-1);
    return (0);
}

int add_incantation(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 0;

    if (get_array_len(parsed_command) != 1)
        return (-1);
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = INCANTATION;
            server->game_data.event[i].time_counter = INCANTATION_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[INCANTATION - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL ||
    check_incantation_condition(&server->game_data, i, idx, true) == -1)
        return (-1);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
