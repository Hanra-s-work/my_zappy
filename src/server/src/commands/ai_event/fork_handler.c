/*
** EPITECH PROJECT, 2024
** server
** File description:
** fork_handler
*/

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static void add_new_player_data(server_handler_t *server, const int new_num,
    char *name, const int idx)
{
    int i = 0;
    int dir = rand() % 4;

    for (; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].team_name == NULL) {
            break;
        }
    }
    server->game_data.clients[i].client_num = new_num;
    server->game_data.clients[i].direction = dir + 1;
    server->game_data.clients[i].pos[0] =
    server->game_data.clients[idx].pos[0];
    server->game_data.clients[i].pos[1] =
    server->game_data.clients[idx].pos[1];
    server->game_data.clients[i].ressources = DEFAULT_RESSOURCES;
    server->game_data.clients[i].level = 1;
    server->game_data.clients[i].team_name = name;
    server->game_data.clients[i].time_life = PLAYER_TIME;
    server->game_data.clients[i].is_connected = false;
    server->game_data.clients[i].fd = UNKNOWN;
}

static void send_successful_fork(server_handler_t *server, const int new_num,
    const int idx)
{
    char str[MAX_BUFFER_SIZE];

    write_to_client(server->game_data.clients[idx].fd, ALL_FINE);
    sprintf(str, "enw #%d #%d %d %d\n",
    new_num,
    server->game_data.clients[idx].client_num,
    server->game_data.clients[idx].pos[0],
    server->game_data.clients[idx].pos[1]);
    write_to_graphics_clients(server->game_data.clients, str);
}

void do_fork(server_handler_t *server, event_t event)
{
    int new_num = 1;
    int idx = get_client(server->game_data.clients, event.fd);
    char *name = NULL;

    for (int i = 0; server->game_data.teams[i].team_name != NULL; i++) {
        new_num += server->game_data.teams[i].client_total;
        if (strcmp(server->game_data.teams[i].team_name,
        server->game_data.clients[idx].team_name) == 0) {
            server->game_data.teams[i].client_total++;
        }
    }
    name = strdup(server->game_data.clients[idx].team_name);
    if (name == NULL) {
        write_to_client(event.fd, AI_COMMAND_FAILED);
        return;
    }
    add_new_player_data(server, new_num, name, idx);
    send_successful_fork(server, new_num, idx);
}

static void send_to_gui_fork_started(server_handler_t *server,
    const cli_t client)
{
    char str[MAX_BUFFER_SIZE];

    sprintf(str, "pfk #%d\n", client.client_num);
    write_to_graphics_clients(server->game_data.clients, str);
}

int add_fork(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 1)
        return (-1);
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = FORK;
            server->game_data.event[i].time_counter = FORK_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[FORK - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL) {
        send_to_gui_fork_started(server, server->game_data.clients[idx]);
        return (0);
    }
    delete_event(&server->game_data.event[i]);
    return (-1);
}
