/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** check_arg_has_value.c
*/

#include <string.h>

#include "arg_parse.h"

int is_param(const char *str, const struct option_list_s *opt_list)
{
    for (int i = 0; i < NB_PARAM; ++i) {
        if (strcmp(str, opt_list[i].option.name) == 0) {
            return (i);
        }
    }
    return (-1);
}

static int is_str_option(const char *str, int *nb_param)
{
    int tmp;

    if (str[0] == '-') {
        tmp = is_param(str, SERVER_OPTION);
        if (tmp != -1)
            ++(*nb_param);
        else
            return (-1);
    } else {
        return (1);
    }
    return (0);
}

int get_nb_parameter(int ac, const char **av)
{
    int nb_param = 0;

    for (int i = 1; i < ac - 1; ++i) {
        if (is_str_option(av[i], &nb_param) == -1)
            return (-1);
    }
    return (nb_param);
}
