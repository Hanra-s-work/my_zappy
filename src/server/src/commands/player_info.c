/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** player_info.c
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "commands.h"

int player_position_request(server_handler_t *server, char **args,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 3);

    if (int_to_str_data == NULL)
        return (EXIT_FAILURE);
    if (get_array_len(args) != 2) {
        free_array(int_to_str_data);
        return (command_parameter_error(server, idx));
    }
    asprintf(&int_to_str_data[0], "%d", server->game_data.clients[idx]
        .client_num);
    asprintf(&int_to_str_data[1], "%d", server->game_data.clients[idx]
        .pos[0]);
    asprintf(&int_to_str_data[2], "%d", server->game_data.clients[idx]
        .pos[1]);
    write(server->game_data.clients[idx].fd, PLAYER_POSITION_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[0],
        strlen(int_to_str_data[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[1],
        strlen(int_to_str_data[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[2],
        strlen(int_to_str_data[2]));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
    free_array(int_to_str_data);
    return (EXIT_SUCCESS);
}

int player_level_request(server_handler_t *server, char **args,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 2);

    if (get_array_len(args) != 2)
        return (command_parameter_error(server, idx));
    if (int_to_str_data == NULL)
        return (EXIT_FAILURE);
    asprintf(&int_to_str_data[0], "%d", server->game_data.clients[idx]
        .client_num);
    asprintf(&int_to_str_data[1], "%d", server->game_data.clients[idx]
        .level);
    write(server->game_data.clients[idx].fd, PLAYER_LEVEL_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[0],
        strlen(int_to_str_data[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[1],
          strlen(int_to_str_data[1]));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
    free_array(int_to_str_data);
    return (EXIT_SUCCESS);
}

static void write_end_of_inv_content(server_handler_t *server, const int idx,
    char **int_to_str_data)
{
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, int_to_str_data[3],
        strlen(int_to_str_data[3]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[4],
        strlen(int_to_str_data[4]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[5],
        strlen(int_to_str_data[5]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[6],
        strlen(int_to_str_data[6]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[7],
        strlen(int_to_str_data[7]));
}

int player_inventory_request(server_handler_t *server, char **args,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 8);

    if (get_array_len(args) != 2)
        return (command_parameter_error(server, idx));
    if (int_to_str_data == NULL)
        return (EXIT_FAILURE);
    asprintf(&int_to_str_data[0], "%d", server->game_data.clients[idx]
        .client_num);
    asprintf(&int_to_str_data[1], "%d", server->game_data.clients[idx]
        .ressources.food_nb);
    asprintf(&int_to_str_data[2], "%d", server->game_data.clients[idx]
        .ressources.linemate_nb);
    asprintf(&int_to_str_data[3], "%d", server->game_data.clients[idx]
        .ressources.food_nb);
    asprintf(&int_to_str_data[4], "%d", server->game_data.clients[idx]
        .client_num);
    asprintf(&int_to_str_data[5], "%d", server->game_data.clients[idx]
        .ressources.food_nb);
    asprintf(&int_to_str_data[6], "%d", server->game_data.clients[idx]
        .client_num);
    asprintf(&int_to_str_data[7], "%d", server->game_data.clients[idx]
        .ressources.food_nb);
    write(server->game_data.clients[idx].fd, PLAYER_INVENTORY_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[0],
        strlen(int_to_str_data[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[1],
        strlen(int_to_str_data[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, int_to_str_data[2],
        strlen(int_to_str_data[2]));
    write_end_of_inv_content(server, idx, int_to_str_data);
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
    free_array(int_to_str_data);
    return (EXIT_SUCCESS);
}
