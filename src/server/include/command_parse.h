/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** command_parse.h
*/

#ifndef MY_ZAPPY_COMMAND_PARSE_H
    #define MY_ZAPPY_COMMAND_PARSE_H

    #include <stdint.h>
    #include <sys/types.h>

    #include "commands.h"
    #include "ai_event.h"
    #include "constants.h"
    #include "server_handler.h"

/**
 * @brief Define structure of a command
 * @param command being the trigger string
 * @param opt Currently unused
 * @param arg_nb number of argument taken by command
 * @param command_fct Function pointer to command function,
 * first parameter is the general structure of server,
 * second parameter is the parsed command,
 * third parameter is the index where the client data is stored in the
 * cli_t array structure
 */
struct command_s {
    char *command;
    char *opt;
    size_t arg_nb;
    int (*command_fct)(server_handler_t *, char **, const int);
};

/**
 * @brief Parse a command using COMMAND_DELIMITER as delimiter
 * @param str Command string to parse
 * @return Parsed command or NULL on error
 */
char **parse_command(char *str);

/**
 * @brief Get all command in buffer
 * (a command is delimited by COMMAND_SEPARATOR)
 * @param buffer Read buffer from server
 * @param buf_size Size of buffer
 * @return Parsed command splited with SPACE as delimiter or NULL on error
 */
char ***parse_buffer(uint8_t *buffer, ssize_t buf_size);

static const struct command_s AI_COMMAND_TABLE[AI_COMMAND_NB] = {
    { "Forward", "", 0, &add_forward },
    { "Right", "", 0, &add_right },
    { "Left", "", 0, &add_left },
    { "Look", "", 0, &add_look },
    { "Inventory", "", 0, &add_inventory },
    { "Broadcast", "", 1, &add_broadcast },
    { "Connect_nbr", "", 0, &do_connect },
    { "Fork", "", 0, &add_fork },
    { "Eject", "", 0, &add_eject },
    { "Take", "", 1, &add_take },
    { "Set", "", 1, &add_set },
    { "Incantation", "", 0, &add_incantation },
};

// static const struct command_s GUI_COMMAND_TABLE[GUI_COMMAND_NB] = {
//     { "msz", "", 0, &map_size_request },
//     { "bct", "", 2, &tile_content_request },
//     { "mct", "", 0, &map_content_request },
//     { "tna", "", 0, &all_team_name_request },
//     { "ppo", "", 1, NULL },
//     { "plv", "", 1, NULL },
//     { "pin", "", 1, NULL },
//     { "sgt", "", 0, &time_unit_request },
//     { "sst", "", 1, &time_unit_modification_request },
// };

static const struct command_s GUI_COMMAND_TABLE[GUI_COMMAND_NB] = {
    { "msz", "", 0, NULL },
    { "bct", "", 2, NULL },
    { "mct", "", 0, NULL },
    { "tna", "", 0, NULL },
    { "ppo", "", 1, NULL },
    { "plv", "", 1, NULL },
    { "pin", "", 1, NULL },
    { "sgt", "", 0, NULL },
    { "sst", "", 1, NULL },
};

static const struct command_s
    COMMAND_TABLE[GUI_COMMAND_NB + AI_COMMAND_NB] = {
    { "Forward", "", 0, &add_forward },
    { "Right", "", 0, &add_right },
    { "Left", "", 0, &add_left },
    { "Look", "", 0, &add_look },
    { "Inventory", "", 0, &add_inventory },
    { "Broadcast", "", 1, &add_broadcast },
    { "Connect_nbr", "", 0, &do_connect },
    { "Fork", "", 0, &add_fork },
    { "Eject", "", 0, &add_eject },
    { "Take", "", 1, &add_take },
    { "Set", "", 1, &add_set },
    { "Incantation", "", 0, &add_incantation },
    { "msz", "", 0, NULL },
    { "bct", "", 2, NULL },
    { "mct", "", 0, NULL },
    { "tna", "", 0, NULL },
    { "ppo", "", 1, NULL },
    { "plv", "", 1, NULL },
    { "pin", "", 1, NULL },
    { "sgt", "", 0, NULL },
    { "sst", "", 1, NULL },
};

#endif //MY_ZAPPY_COMMAND_PARSE_H
