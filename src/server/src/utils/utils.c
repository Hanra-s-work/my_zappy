/*
** EPITECH PROJECT, 2024
** server
** File description:
** free
*/

#include <string.h>
#include <stdlib.h>
#include "arg_parse.h"
#include "utils.h"

void free_array(void *to_free)
{
    void **array = (void **)to_free;

    if (array == NULL) {
        return;
    }
    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
}

void free_args(struct arg_s **args, size_t size)
{
    char **tmp;

    for (size_t i = 0; i < size; ++i) {
        if (strcmp(args[i]->name, "-n") != 0) {
            free(args[i]->value);
        } else {
            tmp = args[i]->value;
            tmp[args[i]->nb_value] = NULL;
            free_array(tmp);
        }
        free(args[i]->name);
        free(args[i]);
    }
<<<<<<<< HEAD:src/server/src/utils/free.c
    free(args);
========
>>>>>>>> origin/server_command_parse:src/server/src/utils/utils.c
}