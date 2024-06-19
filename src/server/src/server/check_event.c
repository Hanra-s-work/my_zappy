/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** check_event
*/

#include <stdio.h>

#include "utils.h"
#include "ai_event.h"
#include "server_handler.h"
#include "client_management.h"

static void check_players_life(server_handler_t *server)
{
    char str[MAX_BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].is_connected == true) {
            server->game_data.clients[i].time_life--;
        }
        if (server->game_data.clients[i].time_life == 0) {
            write_to_client(server->game_data.clients[i].fd, AI_DIED);
            sprintf(str, "pdi #%d\n", server->game_data.clients[i].client_num);
            write_to_graphics_clients(server->game_data.clients, str);
            FD_CLR(server->game_data.clients[i].fd, &server->current_fd);
            delete_client(server->game_data.clients,
            server->game_data.clients[i].fd);
        }
    }
}

static void check_food_spawn(game_data_t *game)
{
    game->event[0].time_counter--;
    if (game->event[0].time_counter == 0) {
        refill_map(game);
    }
    game->event[0].time_counter = SPAWN_TIME;
}

static void check_which_event_2(game_data_t *game, const int idx)
{
    if (game->event[idx].type == FORK)
        return;
    if (game->event[idx].type == EJECT)
        return;
    if (game->event[idx].type == TAKE)
        return;
    if (game->event[idx].type == SET)
        return;
    if (game->event[idx].type == INCANTATION)
        return;
}

static void check_which_event(game_data_t *game, const int idx)
{
    if (game->event[idx].type == FORWARD)
        return;
    if (game->event[idx].type == LEFT_EVENT)
        return;
    if (game->event[idx].type == RIGHT_EVENT)
        return;
    if (game->event[idx].type == LOOK)
        return;
    if (game->event[idx].type == INVENTORY)
        return;
    if (game->event[idx].type == BROADCAST)
        return;
    check_which_event_2(game, idx);
}

void check_event(server_handler_t *server)
{
    check_players_life(server);
    check_food_spawn(&server->game_data);
    for (int i = 1; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            continue;
        }
        server->game_data.event[i].time_counter--;
        if (server->game_data.event[i].time_counter == 0) {
            check_which_event(&server->game_data, i);
            delete_event(&server->game_data.event[i]);
        }
    }
}
