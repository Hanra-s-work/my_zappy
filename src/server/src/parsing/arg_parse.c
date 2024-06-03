/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** arg_parse.c
*/
#include <string.h>
#include "arg_parse.h"
#include "utils.h"

int get_nb_mandatory_option(void)
{
    int nb_mandatory = 0;

    for (int i = 0; i < NB_PARAM; ++i) {
        if (SERVER_OPTION[i].option.mandatory)
            ++nb_mandatory;
    }
    return (nb_mandatory);
}

struct arg_s **get_zappy_argv(int ac, const char **av,
    struct option_list_s *opt_list)
{
    struct arg_s **args = malloc(sizeof(struct arg_s *) * ac);

    if (args == NULL)
        return (NULL);
    for (int i = 0; i < ac; ++i) {
        args[i] = get_arg_value(ac, av, &opt_list[i].option);
        if (args[i] == NULL) {
            free(args);
            return (NULL);
        }

    }
    return (args);
}

static void get_multiple_value(const char **av, int idx, struct arg_s *arg)
{
    int i = 1;
    char **tmp;

    while (av[idx + i][0] != '-') {
        ++arg->nb_value;
        ++i;
    }
    arg->value = malloc(sizeof(char *) * (arg->nb_value + 1));
    if (arg->value == NULL)
        return;
    tmp = arg->value;
    for (size_t j = 0; j < arg->nb_value; ++j) {
        tmp[j] = strdup(av[idx + j]);
        if (tmp[j] == NULL) {
            arg->value = NULL;
            return;
        }
    }
}

static int param_has_mul_val(int idx, struct arg_s *arg, const char **av,
    struct option_s *param)
{
    if (strcmp(av[idx], param->name) == 0) {
        if (param->has_multiple_arg) {
            get_multiple_value(av, idx, arg);
            return (0);
        }
        arg->value = strdup(av[idx + 1]);
        arg->nb_value = 1;
        return (0);
    }
    return (1);
}

struct arg_s *get_arg_value(int ac, const char **av, struct option_s *param)
{
    struct arg_s *arg = malloc(sizeof(struct arg_s) * 1);

    if (arg == NULL)
        return (NULL);
    arg->name = strdup(param->name);
    if (arg->name == NULL) {
        free(arg);
        return (NULL);
    }
    for (int i = 0; i < ac; ++i) {
        if (param_has_mul_val(i, arg, av, param) == 0)
            return (arg);
    }
    free(arg->name);
    free(arg);
    return NULL;
}
