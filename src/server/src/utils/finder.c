/*
** EPITECH PROJECT, 2024
** server
** File description:
** finder
*/

#include <string.h>

#include "arg_parse.h"

void *find_value_by_param(const struct arg_s **arguments, char *param)
{
    int index = 0;

    for (; index < NB_PARAM; index++) {
        if (arguments[index] == NULL || arguments[index]->name == NULL) {
            break;
        }
        if (strcmp(arguments[index]->name, param) == 0) {
            return (arguments[index]->value);
        }
    }
    return (NULL);
}

int find_index_by_param(const struct arg_s **arguments, char *param)
{
    int index = 0;

    for (; index < NB_PARAM; index++) {
        if (arguments[index] == NULL || arguments[index]->name == NULL) {
            break;
        }
        if (strcmp(arguments[index]->name, param) == 0) {
            return (index);
        }
    }
    return (-1);
}
