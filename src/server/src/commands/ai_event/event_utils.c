/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** event_utils
*/

#include "utils.h"
#include "server_handler.h"

void delete_event(event_t *event)
{
    free_array(event->args);
    if (event->indexes != NULL) {
        free(event->indexes);
    }
    *event = DEFAULT_EVENT;
}

void delete_all_event(event_t event[MAX_EVENT])
{
    for (int i = 0; i < MAX_EVENT; i++) {
        if (event[i].fd != UNKNOWN) {
            delete_event(&event[i]);
        }
    }
}

static void set_up_down(game_data_t *game, const int idx, int *y)
{
    if (game->clients[idx].direction == UP) {
        if (*y == 0)
            *y = game->map_size[1] - 1;
        else
            (*y)--;
    }
    if (game->clients[idx].direction == DOWN) {
        if (*y == game->map_size[1] - 1)
            *y = 0;
        else
            (*y)--;
    }
}

void go_in_good_direction(game_data_t *game, const int idx, int *x, int *y)
{
    game->map[*y][*x].player_nb--;
    if (game->clients[idx].direction == LEFT) {
        if (*x == 0)
            *x = game->map_size[0] - 1;
        else
            (*x)--;
    }
    if (game->clients[idx].direction == RIGHT) {
        if (*x == game->map_size[0] - 1)
            *x = 0;
        else
            (*x)++;
    }
    set_up_down(game, idx, y);
    game->map[*y][*x].player_nb++;
}
