/*
** EPITECH PROJECT, 2024
** server
** File description:
** look_handler
*/

#include <string.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static void check_next(game_data_t game, const int x,
    const int y, char str[INSANE_BUFFER_SIZE])
{
    if (game.map[y][x].ressources.food_nb != 0 &&
        game.map[y][x].ressources.linemate_nb != 0 &&
        game.map[y][x].ressources.deraumere_nb != 0 &&
        game.map[y][x].ressources.sibur_nb != 0 &&
        game.map[y][x].ressources.mendiane_nb != 0 &&
        game.map[y][x].ressources.phiras_nb != 0 &&
        game.map[y][x].ressources.thystame_nb != 0) {
            strcat(str, " ");
        }
}

static void fill_str(game_data_t game, const int x,
    const int y, char str[INSANE_BUFFER_SIZE])
{
    for (int l = 0; l < game.map[y][x].player_nb; l++) {
        strcat(str, "player");
        if (l != game.map[y][x].player_nb - 1)
            check_next(game, x, y, str);
    }
    for (int l = 0; l < game.map[y][x].ressources.food_nb; l++)
        strcat(str, " food");
    for (int l = 0; l < game.map[y][x].ressources.linemate_nb; l++)
        strcat(str, " linemate");
    for (int l = 0; l < game.map[y][x].ressources.deraumere_nb; l++)
        strcat(str, " deraumere");
    for (int l = 0; l < game.map[y][x].ressources.sibur_nb; l++)
        strcat(str, " sibur");
    for (int l = 0; l < game.map[y][x].ressources.mendiane_nb; l++)
        strcat(str, " mendiane");
    for (int l = 0; l < game.map[y][x].ressources.phiras_nb; l++)
        strcat(str, " phiras");
    for (int l = 0; l < game.map[y][x].ressources.thystame_nb; l++)
        strcat(str, " thystame");
}

static void check_values(server_handler_t *server, int *x, int *y)
{
    if (*x < 0)
        *x += server->game_data.map_size[0];
    if (*x >= server->game_data.map_size[0])
        *x -= server->game_data.map_size[0];
    if (*y < 0)
        *y += server->game_data.map_size[1];
    if (*y >= server->game_data.map_size[1])
        *y -= server->game_data.map_size[1];
}

static void look_up(server_handler_t *server, const int idx, int **pos,
    char str[INSANE_BUFFER_SIZE])
{
    int player_x = server->game_data.clients[idx].pos[0];
    int player_y = server->game_data.clients[idx].pos[1] - (*pos)[1];
    int loop_x = 0;

    if ((*pos)[0] != 2) {
        loop_x = ((*pos)[0] / 2) * (-1);
        loop_x++;
    }
    player_x += loop_x;
    player_y += 2;
    for (int i = 0; i < (*pos)[0] - 1; i++) {
        check_values(server, (&player_x), &player_y);
        fill_str(server->game_data, player_x, player_y, str);
        player_x++;
        if (i != (*pos)[0] - 2)
            strcat(str, ", ");
    }
    (*pos)[0] += 2;
    (*pos)[1] += 1;
}

static void look_left(server_handler_t *server, const int idx, int **pos,
    char str[INSANE_BUFFER_SIZE])
{
    int player_x = server->game_data.clients[idx].pos[0] - (*pos)[0];
    int player_y = server->game_data.clients[idx].pos[1];
    int loop_y = 0;

    if ((*pos)[1] != 2) {
        loop_y = ((*pos)[1] / 2);
        loop_y--;
    }
    player_x += 2;
    player_y += loop_y;
    for (int i = 0; i < (*pos)[1] - 1; i++) {
        check_values(server, &player_x, &player_y);
        fill_str(server->game_data, player_x, player_y, str);
        player_y--;
        if (i != (*pos)[1] - 2)
            strcat(str, ",");
    }
    (*pos)[0] += 1;
    (*pos)[1] += 2;
}

static void look_down(server_handler_t *server, const int idx, int **pos,
    char str[INSANE_BUFFER_SIZE])
{
    int player_x = server->game_data.clients[idx].pos[0];
    int player_y = server->game_data.clients[idx].pos[1] + (*pos)[1];
    int loop_x = 0;

    if ((*pos)[0] != 2) {
        loop_x = ((*pos)[0] / 2) * (-1);
        loop_x++;
    }
    player_x += loop_x;
    player_y -= 2;
    for (int i = 0; i < (*pos)[0] - 1; i++) {
        check_values(server, &player_x, &player_y);
        fill_str(server->game_data, player_x, player_y, str);
        player_x++;
        if (i != (*pos)[0] - 2)
            strcat(str, ",");
    }
    (*pos)[0] += 2;
    (*pos)[1] += 1;
}

static void look_right(server_handler_t *server, const int idx, int **pos,
    char str[INSANE_BUFFER_SIZE])
{
    int player_x = server->game_data.clients[idx].pos[0] + (*pos)[0];
    int player_y = server->game_data.clients[idx].pos[1];
    int loop_y = 0;

    if ((*pos)[1] != 2) {
        loop_y = ((*pos)[1] / 2) * (-1);
        loop_y++;
    }
    player_x -= 2;
    player_y += loop_y;
    for (int i = 0; i < (*pos)[1] - 1; i++) {
        check_values(server, &player_x, &player_y);
        fill_str(server->game_data, player_x, player_y, str);
        player_y++;
        if (i != (*pos)[1] - 2)
            strcat(str, ", ");
    }
    (*pos)[0] += 1;
    (*pos)[1] += 2;
}

void generic_look(server_handler_t *server,
    char str[INSANE_BUFFER_SIZE], const int idx, const int size)
{
    direction_t direction = server->game_data.clients[idx].direction;
    int *pos = malloc(sizeof(int) * 2);

    pos[0] = 2;
    pos[1] = 2;
    strcat(str, "[");
    for (int a = 0; a < size; a++) {
        if (a != 0)
            strcat(str, ", ");
        if (direction == UP)
            look_up(server, idx, &pos, str);
        if (direction == DOWN)
            look_down(server, idx, &pos, str);
        if (direction == LEFT)
            look_left(server, idx, &pos, str);
        if (direction == RIGHT)
            look_right(server, idx, &pos, str);
    }
    free(pos);
    strcat(str, "]\n");
}

void do_look(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    char str[INSANE_BUFFER_SIZE];

    memset(str, '\0', INSANE_BUFFER_SIZE);
    if (server->game_data.clients->level == 1)
        generic_look(server, str, idx, 1);
    if (server->game_data.clients->level == 2)
        generic_look(server, str, idx, 2);
    if (server->game_data.clients->level == 3)
        generic_look(server, str, idx, 3);
    if (server->game_data.clients->level == 4)
        generic_look(server, str, idx, 4);
    if (server->game_data.clients->level == 5)
        generic_look(server, str, idx, 5);
    if (server->game_data.clients->level == 6)
        generic_look(server, str, idx, 6);
    do_other_look(server, str, idx);
    write_to_client(event.fd, str);
}

int add_look(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 1) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = LOOK;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[LOOK - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
