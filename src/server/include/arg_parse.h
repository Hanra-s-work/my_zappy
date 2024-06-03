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

    #define NB_PARAM 6

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
    { {"-w", true, false, "width of the world", true, NULL } },
    { {"-y", true, false, "height of the world", true, NULL} },
    { {"-n", true, true, "name of the team", true, NULL} },
    { {"-c", true, false, "number of authorized clients per team", true, NULL} },
    { {"-f", true, false, "reciprocal of time unit for execution of actions",
       false, (void *) 100} },
};

int get_nb_mandatory_option(void);

int check_mandatory_set(int ac, const char **av);

struct arg_s *get_arg_value(int ac, const char **av, struct option_s *param);

struct arg_s **get_zappy_argv(int ac, const char **av,
    struct option_list_s *opt_list);

#endif //ZAPPY_ARG_PARSE_H
