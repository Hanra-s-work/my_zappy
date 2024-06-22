/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** player_info.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "commands.h"

static int search_client_num_index(server_handler_t *server,
    const int client_num)
{
    if (client_num <= 0) {
        return (-1);
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].client_num == client_num &&
        server->game_data.clients[i].is_connected == true) {
            return (i);
        }
    }
    return (-1);
}

static void fill_for_position(server_handler_t *server, const int idx,
    char **to_str)
{
    asprintf(&to_str[0], "%d", server->game_data.clients[idx].client_num);
    asprintf(&to_str[1], "%d", server->game_data.clients[idx].pos[0]);
    asprintf(&to_str[2], "%d", server->game_data.clients[idx].pos[1]);
    asprintf(&to_str[3], "%d", server->game_data.clients[idx].direction);
}

static void write_position(server_handler_t *server, const int idx,
    char **to_str)
{
    write(server->game_data.clients[idx].fd, PLAYER_POSITION_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[0], strlen(to_str[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[1], strlen(to_str[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[2], strlen(to_str[2]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[3], strlen(to_str[2]));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
}

int player_position_request(server_handler_t *server, char **args,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 4);
    int client_idx = 0;

    if (int_to_str_data == NULL)
        return (EXIT_FAILURE);
    if (get_array_len(args) != 2) {
        free_array_size_n(int_to_str_data, 0);
        return (command_parameter_error(server, idx));
    }
    client_idx = search_client_num_index(server, atoi(args[1]));
    if (client_idx == -1) {
        free_array_size_n(int_to_str_data, 0);
        return (command_parameter_error(server, idx));
    }
    fill_for_position(server, client_idx, int_to_str_data);
    write_position(server, idx, int_to_str_data);
    free_array_size_n(int_to_str_data, 4);
    return (EXIT_SUCCESS);
}

static void fill_for_level(server_handler_t *server, const int idx,
    char **to_str)
{
    asprintf(&to_str[0], "%d", server->game_data.clients[idx].client_num);
    asprintf(&to_str[1], "%d", server->game_data.clients[idx].level);
}

static void write_level(server_handler_t *server, const int idx, char **to_str)
{
    write(server->game_data.clients[idx].fd, PLAYER_LEVEL_COMMAND,
    COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[0], strlen(to_str[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[1], strlen(to_str[1]));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
}

int player_level_request(server_handler_t *server, char **args,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 2);
    int client_idx = 0;

    if (int_to_str_data == NULL)
        return (EXIT_FAILURE);
    if (get_array_len(args) != 2) {
        free_array_size_n(int_to_str_data, 0);
        return (command_parameter_error(server, idx));
    }
    client_idx = search_client_num_index(server, atoi(args[1]));
    if (client_idx == -1) {
        free_array_size_n(int_to_str_data, 0);
        return (command_parameter_error(server, idx));
    }
    fill_for_level(server, client_idx, int_to_str_data);
    write_level(server, idx, int_to_str_data);
    free_array_size_n(int_to_str_data, 2);
    return (EXIT_SUCCESS);
}

static void fill_for_inventory(server_handler_t *server, const int idx,
    char **to_str)
{
    asprintf(&to_str[0], "%d", server->game_data.clients[idx].client_num);
    asprintf(&to_str[1], "%d", server->game_data.clients[idx].ressources
    .food_nb);
    asprintf(&to_str[2], "%d", server->game_data.clients[idx].ressources
    .linemate_nb);
    asprintf(&to_str[3], "%d", server->game_data.clients[idx].ressources
    .deraumere_nb);
    asprintf(&to_str[4], "%d", server->game_data.clients[idx].ressources
    .sibur_nb);
    asprintf(&to_str[5], "%d", server->game_data.clients[idx].ressources
    .mendiane_nb);
    asprintf(&to_str[6], "%d", server->game_data.clients[idx].ressources
    .phiras_nb);
    asprintf(&to_str[7], "%d", server->game_data.clients[idx].ressources
    .thystame_nb);
}

static void write_inventory(server_handler_t *server, const int idx,
    char **to_str)
{
    write(server->game_data.clients[idx].fd, PLAYER_INVENTORY_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[0], strlen(to_str[0]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[1], strlen(to_str[1]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[2], strlen(to_str[2]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[3], strlen(to_str[3]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[4], strlen(to_str[4]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[5], strlen(to_str[5]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[6], strlen(to_str[6]));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR, 1);
    write(server->game_data.clients[idx].fd, to_str[7], strlen(to_str[7]));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR, 1);
}

int player_inventory_request(server_handler_t *server, char **args,
    const int idx)
{
    char **int_to_str_data = malloc(sizeof(char *) * 8);
    int client_idx = 0;

    if (int_to_str_data == NULL)
        return (EXIT_FAILURE);
    if (get_array_len(args) != 2) {
        free_array_size_n(int_to_str_data, 0);
        return (command_parameter_error(server, idx));
    }
    client_idx = search_client_num_index(server, atoi(args[1]));
    if (client_idx == -1) {
        free_array_size_n(int_to_str_data, 0);
        return (command_parameter_error(server, idx));
    }
    fill_for_inventory(server, client_idx, int_to_str_data);
    write_inventory(server, idx, int_to_str_data);
    free_array_size_n(int_to_str_data, 8);
    return (EXIT_SUCCESS);
}
