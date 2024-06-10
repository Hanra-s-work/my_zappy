/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** check_arg_mandatory.c
*/

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "arg_parse.h"

int get_nb_mandatory_option(const struct option_list_s *opt_list)
{
    int nb_mandatory = 0;

    for (int i = 0; i < NB_PARAM; ++i) {
        if (opt_list[i].option.mandatory)
            ++nb_mandatory;
    }
    return (nb_mandatory);
}

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

static char **get_list_mandatory(const struct option_list_s *opt_list)
{
    int nb_mandatory = get_nb_mandatory_option(opt_list);
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

int check_mandatory_set(int ac, const char **av, int nb_param,
    const struct option_list_s *opt_list)
{
    int nb_mandatory = get_nb_mandatory_option(opt_list);
    char **mandatory = get_list_mandatory(opt_list);
    int mandatory_present = 0;

    if (mandatory == NULL || nb_param < nb_mandatory)
        return (write_error_msg("Error: Not enough parameters.\n"));
    for (int i = 0; i < nb_mandatory; ++i) {
        is_mandatory(ac, &mandatory_present, av, mandatory[i]);
    }
    if (nb_mandatory != mandatory_present) {
        free_array(mandatory);
        free(mandatory);
        return (write_error_msg("Error: A parameter was not recognised.\n"));
    }
    free_array(mandatory);
    free(mandatory);
    return (0);
}
