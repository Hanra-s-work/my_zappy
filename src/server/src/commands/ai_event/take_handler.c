/*
** EPITECH PROJECT, 2024
** server
** File description:
** take_handler
*/

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static void write_take_to_gui(server_handler_t *server, const int num)
{
    char str[MAX_BUFFER_SIZE];

    sprintf(str, "pgt %d 1\n", num);
    write_to_graphics_clients(server->game_data.clients, str);
}

static int check_player_ressources(int *player_ressources, int *map_ressources)
{
    if (*map_ressources == 0) {
        return (-1);
    }
    (*player_ressources)++;
    (*map_ressources)--;
    return (0);
}

static int check_other_player_ressources_2(server_handler_t *server,
    event_t event, const int idx, const int *pos)
{
    int status = 1;

    if (strcmp(event.args[0], "deraumere") == 0)
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.deraumere_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.deraumere_nb);
    if (strcmp(event.args[0], "sibur") == 0)
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.sibur_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.sibur_nb);
    return (status);
}

static int check_other_player_ressources(server_handler_t *server,
    event_t event, const int idx, const int *pos)
{
    int status = 1;

    if (strcmp(event.args[0], "mendiane") == 0)
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.mendiane_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.mendiane_nb);
    if (strcmp(event.args[0], "phiras") == 0)
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.phiras_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.phiras_nb);
    if (strcmp(event.args[0], "thystame") == 0)
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.thystame_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.thystame_nb);
    return (status);
}

static int check_food(server_handler_t *server, event_t event)
{
    int status = 1;
    int idx = get_client(server->game_data.clients, event.fd);
    int *pos = server->game_data.clients[idx].pos;

    if (strcmp(event.args[0], "food") == 0) {
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.food_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.food_nb);
    }
    if (status == 0) {
        server->game_data.clients[idx].time_life += ADD_TIME_LIFE;
    }
    return (status);
}

void do_take(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    int *pos = server->game_data.clients[idx].pos;
    int status = 1;

    if (strcmp(event.args[0], "linemate") == 0)
        status = check_player_ressources(
        &server->game_data.clients[idx].ressources.linemate_nb,
        &server->game_data.map[pos[1]][pos[0]].ressources.linemate_nb);
    if (status == 1)
        status = check_other_player_ressources_2(server, event, idx, pos);
    if (status == 1)
        status = check_other_player_ressources(server, event, idx, pos);
    if (status == 1)
        status = check_food(server, event);
    if (status == 0) {
        write_to_client(event.fd, ALL_FINE);
        write_take_to_gui(server, server->game_data.clients[idx].client_num);
    } else
        write_to_client(event.fd, AI_COMMAND_FAILED);
}

int add_take(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 2) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = TAKE;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[TAKE - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
