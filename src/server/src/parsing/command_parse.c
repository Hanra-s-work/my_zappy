/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** command_parse.c
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "command_parse.h"

/**
 * @brief Verify parameter for command
 * @param i Index of command in COMMAND_TABLE
 * @param command array with command and parameter
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int check_command_arg(int i, char **command)
{
    size_t len_command = get_array_len(command);

    if (COMMAND_TABLE[i].arg_nb < len_command - 1)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

/**
 * @brief Verify if command exist and if it is valid
 * @param command array to verify
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int check_command_exist(char **command)
{
    int r_val;

    for (int i = 0; i < CLIENT_COMMAND_NB + GUI_COMMAND_NB; ++i) {
        if (strcmp(command[0], COMMAND_TABLE[i].command) == 0) {
            r_val = check_command_arg(i, command);
            return (r_val);
        }
    }
    return (EXIT_FAILURE);
}

char **parse_command(char *str)
{
    char **command = NULL;

    command = str_to_word_array(str, COMMAND_DELIMITER);
    if (command == NULL)
        return (NULL);
    if (check_command_exist(command) == EXIT_FAILURE) {
        free_array(command);
        return (NULL);
    }
    return (command);
}

/**
 * @brief This function split each command received delimited by \\n into an
 * array of command word
 * @param command_nb Number of command in buf
 * @param buf Command list
 * @return Char *** of size command_nb + 1 or NULL on error
 */
static char ***parse_individual_command(char **buf)
{
    char ***commands;
    size_t command_nb = get_array_len(buf);

    commands = malloc(sizeof(char **) * (command_nb + 1));
    if (commands == NULL) {
        free_array(buf);
        return (NULL);
    }
    for (size_t i = 0; i < command_nb; ++i) {
        commands[i] = parse_command(buf[i]);
        if (commands[i] == NULL) {
            free_array_size_n(commands, i);
            return (NULL);
        }
    }
    commands[command_nb] = NULL;
    return (commands);
}

char ***parse_buffer(uint8_t *buffer, ssize_t buf_size)
{
    char *str = malloc(sizeof(char) * (buf_size + 2));
    char **buf;
    char ***commands;

    if (str == NULL)
        return (NULL);
    (void) memcpy(str, buffer, buf_size);
    str[buf_size + 1] = '\0';
    if ((buf = str_to_word_array(str, COMMAND_SEPARATOR)) == NULL) {
        free(str);
        return (NULL);
    }
    if ((commands = parse_individual_command(buf)) == NULL) {
        free(str);
        free_array(buf);
        return (NULL);
    }
    free(str);
    free_array(buf);
    return (commands);
}
