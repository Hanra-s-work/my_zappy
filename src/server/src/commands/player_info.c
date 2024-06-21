/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** player_info.c
*/

#include <unistd.h>

#include "commands.h"

int player_position_request(server_handler_t *server, char **args,
    const int idx)
{
    (void) args;
    write(server->game_data.clients[idx].fd, PLAYER_POSITION_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .client_num, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .pos[0], sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .pos[1], sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR,
        1);
    return (EXIT_SUCCESS);
}

int player_level_request(server_handler_t *server, char **args,
    const int idx)
{
    (void) args;
    write(server->game_data.clients[idx].fd, PLAYER_LEVEL_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .client_num, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .level, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR,
        1);
    return (EXIT_SUCCESS);
}

static void write_end_of_inv_content(server_handler_t *server, const int idx)
{
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.deraumere_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.sibur_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.mendiane_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.phiras_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.thystame_nb, sizeof(int));
}

int player_inventory_request(server_handler_t *server, char **args,
    const int idx)
{
    (void) args;
    write(server->game_data.clients[idx].fd, PLAYER_INVENTORY_COMMAND,
        COMMAND_ID_LEN);
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .client_num, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.food_nb, sizeof(int));
    write(server->game_data.clients[idx].fd, COMMAND_DELIMITER_STR,
        1);
    write(server->game_data.clients[idx].fd, &server->game_data.clients[idx]
        .ressources.linemate_nb, sizeof(int));
    write_end_of_inv_content(server, idx);
    write(server->game_data.clients[idx].fd, COMMAND_SEPARATOR_STR,
        1);
    return (EXIT_SUCCESS);
}
