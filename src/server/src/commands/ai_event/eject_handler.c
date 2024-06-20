/*
** EPITECH PROJECT, 2024
** server
** File description:
** eject_handler
*/

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static void set_up_down(game_data_t *game, const int idx,
    int *pos[2])
{
    if (game->clients[idx].direction == UP) {
        if (*pos[1] == 0)
            *pos[1] = game->map_size[1] - 1;
        else
            *pos[1]--;
    }
    if (game->clients[idx].direction == DOWN) {
        if (*pos[1] == game->map_size[1] - 1)
            *pos[1] = 0;
        else
            *pos[1]--;
    }
}

static void eject_in_good_direction(game_data_t *game, const int idx,
    int *pos[2])
{
    game->map[*pos[1]][*pos[0]].player_nb--;
    if (game->clients[idx].direction == LEFT) {
        if (*pos[0] == 0)
            *pos[0] = game->map_size[0] - 1;
        else
            *pos[0]--;
    }
    if (game->clients[idx].direction == RIGHT) {
        if (*pos[0] == game->map_size[0] - 1)
            *pos[0] = 0;
        else
            *pos[0]++;
    }
    set_up_down(game, idx, pos);
    game->map[*pos[1]][*pos[0]].player_nb++;
}

void do_eject(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    int player_pos[2] = server->game_data.clients[idx].pos;

    if (server->game_data.map[player_pos[1]][player_pos[0]].player_nb < 2) {
        write_to_client(event.fd, AI_COMMAND_FAILED);
        return;
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].pos[0] == player_pos[0] &&
        server->game_data.clients[i].pos[1] == player_pos[1]) {
            eject_in_good_direction(&server->game_data, idx,
            &server->game_data.clients[i].pos);
        }
    }
}


int add_eject(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 0;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = EJECT;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[EJECT - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
