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

int check_numeral_value(char *str)
{
    char *endptr = NULL;
    long value;

    value = strtol(str, &endptr, 10);
    if (endptr[0] != '\0')
        return (-1);
    if (value < 0)
        return (-1);
    return (0);
}

int check_arg_value_server(struct arg_s **zappy_args)
{
    int r_val;

    for (int i = 0; zappy_args[i] != NULL; ++i) {
        if (strcmp(zappy_args[i]->name, "-n") == 0) {
            r_val = zappy_args[i]->nb_value >= 1 ? 0 : -1;
        } else {
            r_val = check_numeral_value((char *)zappy_args[i]->value);
        }
        if (r_val == -1)
            return (-1);
    }
    return (0);
}
