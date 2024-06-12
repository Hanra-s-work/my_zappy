/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.c
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "arg_parse.h"
#include "utils.h"

int write_error_msg(char *str)
{
    write(STDERR_FILENO, str, strlen(str));
    return (-1);
}

void free_args(struct arg_s **args, size_t size)
{
    char **tmp;

    for (size_t i = 0; i < size; ++i) {
        free(args[i]->name);
        if (args[i]->nb_value == 1) {
            free(args[i]->value);
            continue;
        }
        tmp = args[i]->value;
        for (size_t j = 0; j < args[i]->nb_value; ++j) {
            free(tmp[j]);
        }
    }
}
