/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** arg_parse.h
*/

#ifndef ZAPPY_ARG_PARSE_H
    #define ZAPPY_ARG_PARSE_H

    #include <stdlib.h>
    #include <stdbool.h>

    #include "constants.h"

struct arg_s {
    char *name;
    size_t nb_value;
    void *value;
};

struct option_s {
    char *name;
    bool has_arg;
    bool has_multiple_arg;
    char *help;
    bool mandatory;
    void *default_value;
};

struct option_list_s {
    struct option_s option;
};

static const struct option_list_s SERVER_OPTION[NB_PARAM] = {
    { {"-p", true, false, "port number", true, NULL } },
    { {"-x", true, false, "width of the world", true, NULL } },
    { {"-y", true, false, "height of the world", true, NULL} },
    { {"-n", true, true, "name of the team", true, NULL} },
    { {"-c", true, false, CLIENTS_NB_PARAM, true, NULL} },
    { {"-f", true, false, FREQUENCE_PARAM, false, (void *) 100} },
};

int get_nb_mandatory_option(const struct option_list_s *opt_list);

int check_mandatory_set(int ac, const char **av, int nb_param,
    const struct option_list_s *opt_list);

int is_param(const char *str, const struct option_list_s *opt_list);

int get_nb_parameter(int ac, const char **av);

int get_arg_value(int ac, const char **av,
    const struct option_s *param, struct arg_s **arg);

struct arg_s **get_zappy_args(int ac, const char **av,
    const struct option_list_s *opt_l);

int check_arg_value_server(struct arg_s **zappy_args);

#endif //ZAPPY_ARG_PARSE_H
