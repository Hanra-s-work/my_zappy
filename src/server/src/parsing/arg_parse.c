/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** arg_parse.c
*/
#include <string.h>
#include "arg_parse.h"
#include "utils.h"

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
        tmp[j] = strdup(av[idx + 1 + j]);
        if (tmp[j] == NULL) {
            arg->value = NULL;
            return;
        }
    }
}

static int param_has_mul_val(int idx, struct arg_s *arg, const char **av,
    const struct option_s *param)
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

int get_arg_value(int ac, const char **av,
    const struct option_s *param, struct arg_s **arg)
{
    (*arg) = malloc(sizeof(struct arg_s) * 1);
    if ((*arg) == NULL)
        return (-1);
    (*arg)->name = strdup(param->name);
    (*arg)->nb_value = 0;
    if ((*arg)->name == NULL) {
        free((*arg));
        return (-1);
    }
    for (int i = 0; i < ac; ++i) {
        if (param_has_mul_val(i, *arg, av, param) == 0)
            return (0);
    }
    free((*arg)->name);
    free((*arg));
    return (-1);
}

static int *get_set_param(int ac, const char **av, int nb_param)
{
    int count = 0;
    int *param = malloc(sizeof(int) * nb_param);
    int tmp;

    if (param == NULL)
        return (NULL);
    for (int i = 1; i < ac - 1 && count < nb_param; ++i) {
        tmp = is_param(av[i], SERVER_OPTION);
        if (tmp != -1) {
            param[count] = tmp;
            ++count;
        }
    }
    return (param);
}

struct arg_s **get_zappy_args(int ac, const char **av,
    const struct option_list_s *opt_l)
{
    int nb_param = get_nb_parameter(ac, av);
    int *to_get = get_set_param(ac, av, nb_param);
    struct arg_s **args = malloc(sizeof(struct arg_s *) * (nb_param + 1));

    if (check_mandatory_set(ac, av, nb_param, opt_l) == -1 || args == NULL) {
        free(args);
        free(to_get);
        return (NULL);
    }
    for (int i = 0; i < nb_param; ++i) {
        if (get_arg_value(ac, av, &opt_l[to_get[i]].option, &args[i]) == -1) {
            free_args(args, i);
            free(to_get);
            free(args);
            return (NULL);
        }
    }
    free(to_get);
    args[nb_param] = NULL;
    return (args);
}
