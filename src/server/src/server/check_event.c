/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** check_event
*/

#include <stdio.h>

#include "show.h"
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

static void send_failed_incantation(server_handler_t *server, int idx)
{
    char str[MAX_BUFFER_SIZE];

    sprintf(str, "pie %d %d 0\n",
    server->game_data.clients[idx].pos[0],
    server->game_data.clients[idx].pos[1]);
    write_to_graphics_clients(server->game_data.clients, str);
}

static void check_which_event_2(server_handler_t *server, const int idx)
{
    int i = get_client(server->game_data.clients,
    server->game_data.event[idx].fd);

    if (server->game_data.event[idx].type == FORK)
        do_fork(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == EJECT)
        do_eject(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == TAKE)
        do_take(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == SET)
        do_set(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == INCANTATION) {
        if (check_incantation_condition(&server->game_data, idx, i,
        false) == -1) {
            send_failed_incantation(server, idx);
        }
    }
}

static void check_which_event(server_handler_t *server, const int idx)
{
    if (server->game_data.event[idx].type == FORWARD)
        do_forward(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == LEFT_EVENT)
        do_left(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == RIGHT_EVENT)
        do_right(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == LOOK)
        do_look(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == INVENTORY)
        do_inventory(server, server->game_data.event[idx]);
    if (server->game_data.event[idx].type == BROADCAST)
        do_broadcast(server, server->game_data.event[idx]);
    check_which_event_2(server, idx);
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
            check_which_event(server, i);
            delete_event(&server->game_data.event[i]);
        }
    }
}
