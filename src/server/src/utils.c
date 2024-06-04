/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.c
*/
#include <stdio.h>
#include "arg_parse.h"

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

void free_array(void *to_free)
{
    void **array = (void **)to_free;

    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
}
