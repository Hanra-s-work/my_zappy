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

/**
 * @brief Get the number of mandatory options needed for the server
 * @param opt_list The constant defined with every known command
 * @return 5 because the zappy server has 5 mandatory function
*/
int get_nb_mandatory_option(const struct option_list_s *opt_list);

/**
 * @brief Check if there's every mandatory options in the arguments passed to
 * the program
 * @param ac Number of arguments
 * @param av Variables passed as parameter to the program
 * @param nb_param Number of parameter
 * @param opt_list The constant defined with every known command
 * @return (0) if there's enough parameter, (-1) if not
*/
int check_mandatory_set(int ac, const char **av, int nb_param,
    const struct option_list_s *opt_list);

/**
 * @brief Check if a string is a parameter
 * @param str The string to check
 * @param opt_list The constant defined with every known command
 * @return The index of the parameter in the constants, (-1) if not found
*/
int is_param(const char *str, const struct option_list_s *opt_list);

/**
 * @brief Get the number of parameter passed to the program
 * @param ac Number of arguments
 * @param av Variables passed as parameter to the program
 * @return The number of parameter passed to the program
*/
int get_nb_parameter(int ac, const char **av);

/**
 * @brief Get the variables of a parameter and store it in arg_s structure
 * @param ac Number of arguments
 * @param av Variables passed as parameter to the program
 * @param param A intermediaire structure (option_s) before store it in
 * arg_s structure
 * @param arg The structure where parameters and parameters value are stored
 * @return (0) if values are stored successfully, (-1) if not
*/
int get_arg_value(int ac, const char **av,
    const struct option_s *param, struct arg_s **arg);

/**
 * @brief The principal function to get every arguments
 * @param ac Number of arguments
 * @param av Variables passed as parameter to the program
 * @param param A intermediaire structure (option_s) before store it in
 * arg_s structure
 * @return arg_s the structure where parameters and parameters value are stored
*/
struct arg_s **get_zappy_args(int ac, const char **av,
    const struct option_list_s *opt_l);

/**
 * @brief Check if the values of the parameters are correct
 * @param arguments The structure where parameters and parameters value
 * are stored
 * @param size The size of the structure
 * @return (0) if every values are correct, (-1) if not
*/
int check_values_validity(const struct arg_s **arguments, const size_t size);

#endif //ZAPPY_ARG_PARSE_H
