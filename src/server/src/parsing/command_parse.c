/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** command_parse.c
*/

#include <stdlib.h>
#include "utils.h"
#include "command_parse.h"

char **parse_command(uint8_t *buffer, ssize_t buf_size)
{
    char *str = (char *)buffer;
    char **commands = NULL;

    commands = str_to_word_array(str, "\n");
    return (commands);
}

char ***parse_buffer(uint8_t *buffer, ssize_t buf_size)
{
    char *str = (char *)buffer;
    char **buf;
    char ***commands;
    size_t command_nb;

    buf = str_to_word_array(str, "\n");
    if (buf  == NULL)
        return (NULL);
    command_nb = get_array_len(buf);
    commands = malloc(sizeof(char **) * (command_nb + 1));
    if (commands == NULL) {
        free_array(buf);
        return (NULL);
    }
    for (size_t i = 0; i < command_nb; ++i) {
        commands[i] = parse_command();
        if (commands[i] == NULL) {
            free_array_size_n(commands, i);
            return (NULL);
        }
    }
    commands[command_nb] = NULL;
    return (commands);
}
