/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** broadcast_handler
*/

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static int *direction_to_adjacent_tile(server_handler_t *server, cli_t *sender,
    cli_t *receiver)
{
    int s_r_vector_x = sender->pos[0] - receiver->pos[0];
    int s_r_vector_y = sender->pos[1] - receiver->pos[1];
    int adjacent_tile = malloc(sizeof(int) * 2);

    if (adjacent_tile == NULL)
        return (NULL);
    if (s_r_vector_x < 0)
        adjacent_tile[0] = receiver->pos[0] - 1;
    else if (s_r_vector_x > 0)
        adjacent_tile[0] = receiver->pos[0] + 1;
    else
        adjacent_tile[0] = receiver->pos[0];
    if (s_r_vector_y < 0)
        adjacent_tile[1] = receiver->pos[1] - 1;
    else if (s_r_vector_y > 0)
        adjacent_tile[1] = receiver->pos[1] + 1;
    else
        adjacent_tile[1] = receiver->pos[1];
    return (adjacent_tile);
}

static char *create_broadcast_message(char *text, int *direction)
{
    char *msg;
    char *x;
    char *y;

    if (asprintf(&x, "%d", direction[0]) == -1)
        return (NULL);
    if (asprintf(&y, "%d", direction[1]) == -1)
        return (NULL);
    msg = malloc(sizeof(char) * (strlen(text) + strlen(x) + strlen(y) + 10));
    if (msg == NULL)
        return (NULL);
    msg[0] = '\0';
    strcat(msg, BROADCAST_COMMAND);
    strcat(msg, " ");
    strcat(msg, x);
    strcat(msg, " ");
    strcat(msg, y);
    strcat(msg, ", ");
    strcat(msg, text);
    return (msg);
}

void do_broadcast(server_handler_t *server, event_t event)
{
    int idx = get_client(server->game_data.clients, event.fd);
    int *direction;
    char *msg = NULL;

    write_to_client(event.fd, ALL_FINE);
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (i == idx || server->game_data.clients[i].team_name == NULL ||
        strcmp(server->game_data.clients[i].team_name, GUI_TEAM_NAME) == 0) {
            continue;
        }
        direction = direction_to_adjacent_tile(server,
            &server->game_data.clients[idx], server->game_data.clients[i]);
        if (direction == NULL)
            continue;
        msg = create_broadcast_msg(event.args[1], direction);
        write_to_client(i, msg);
        write_to_client(i, "\n");
        free(msg);
        free(direction);
    }
}

int add_broadcast(server_handler_t *server, char **parsed_command,
    const int idx)
{
    int i = 1;

    if (get_array_len(parsed_command) != 2) {
        return (-1);
    }
    for (; i < MAX_EVENT; i++) {
        if (server->game_data.event[i].fd == UNKNOWN) {
            server->game_data.event[i].fd = server->game_data.clients[idx].fd;
            server->game_data.event[i].type = BROADCAST;
            server->game_data.event[i].time_counter = BASIC_TIME;
            server->game_data.event[i].args = fill_arg_in_event(parsed_command,
            1, AI_COMMAND_TABLE[BROADCAST - 1].arg_nb + 1);
            break;
        }
    }
    if (server->game_data.event[i].args != NULL)
        return (0);
    delete_event(&server->game_data.event[i]);
    return (-1);
}
