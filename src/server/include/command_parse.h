/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** command_parse.h
*/

#ifndef MY_ZAPPY_COMMAND_PARSE_H
    #define MY_ZAPPY_COMMAND_PARSE_H

    #include <stdint.h>
    #include "constants.h"

/**
 * @brief Define structure of a command
 * @command being the trigger string
 * @opt Currently unused
 * @arg_nb number of argument taken by command
 * @command_fct Function pointer to command function
 */
struct command_s {
    char *command;
    char *opt;
    size_t arg_nb;
    char *(*command_fct)(char *, char *, char *);
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

static const struct command_s CLIENT_COMMAND_TABLE[CLIENT_COMMAND_NB] = {
        { "Forward", "", 0, NULL },
        { "Right", "", 0, NULL },
        { "Left", "", 0, NULL },
        { "Look", "", 0, NULL },
        { "Inventory", "", 0, NULL },
        { "Broadcast", "", 1, NULL },
        { "Connect_nbr", "", 0, NULL },
        { "Fork", "", 0, NULL },
        { "Eject", "", 0, NULL },
        { "", "", 0, NULL },
        { "Take", "", 1, NULL },
        { "Set", "", 1, NULL },
        { "Incantation", "", 0, NULL },
};

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
    COMMAND_TABLE[GUI_COMMAND_NB + CLIENT_COMMAND_NB] = {
        { "Forward", "", 0, NULL },
        { "Right", "", 0, NULL },
        { "Left", "", 0, NULL },
        { "Look", "", 0, NULL },
        { "Inventory", "", 0, NULL },
        { "Broadcast", "", 1, NULL },
        { "Connect_nbr", "", 0, NULL },
        { "Fork", "", 0, NULL },
        { "Eject", "", 0, NULL },
        { "", "", 0, NULL },
        { "Take", "", 1, NULL },
        { "Set", "", 1, NULL },
        { "Incantation", "", 0, NULL },
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
