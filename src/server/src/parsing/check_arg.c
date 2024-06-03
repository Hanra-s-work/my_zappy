/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** check_arg.c
*/
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "arg_parse.h"

static void is_mandatory(int ac, int *mandatory_present, const char **av,
    char *mandatory)
{
    for (int j = 1; j < ac - 1; ++j) {
        if (strcmp(mandatory, av[j]) == 0) {
            ++(*mandatory_present);
            return;
        }
    }
}

static char **get_list_mandatory(void)
{
    int nb_mandatory = get_nb_mandatory_option();
    char **mandatory = malloc(sizeof(char *) * (nb_mandatory + 1));
    int mandatory_idx = 0;

    if (mandatory == NULL)
        return (NULL);
    for (int i = 0; i < NB_PARAM; ++i) {
        if (SERVER_OPTION[i].option.mandatory) {
            mandatory[mandatory_idx] = strdup(SERVER_OPTION[i].option.name);
            ++mandatory_idx;
        }
    }
    mandatory[nb_mandatory] = NULL;
    return (mandatory);
}


int check_mandatory_set(int ac, const char **av)
{
    int nb_mandatory = get_nb_mandatory_option();
    char **mandatory = get_list_mandatory();
    int mandatory_present = 0;

    if (mandatory == NULL || (nb_mandatory * 2) > ac) {
        return (-1);
    }
    for (int i = 0; i < nb_mandatory; ++i) {
        is_mandatory(ac, &mandatory_present, av, mandatory[i]);
    }
    if (nb_mandatory != mandatory_present) {
        free_array(mandatory);
        free(mandatory);
        return (-1);
    }
    free_array(mandatory);
    free(mandatory);
    return (0);
}
