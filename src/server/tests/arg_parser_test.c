/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** arg_parser_test.c
*/
#include <criterion/criterion.h>
#include "arg_parse.h"

Test(arg_parser, get_nb_mandatory)
{
    int nb_mandatory = get_nb_mandatory_option(SERVER_OPTION);

    cr_assert_eq(nb_mandatory, 5);
}

Test(arg_parser, check_mandatory_set)
{
    int mandatory_ok;
    const char *av[13] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", NULL};

    mandatory_ok = check_mandatory_set(13, av, 5, SERVER_OPTION);
    cr_assert_eq(mandatory_ok, 0);
}

Test(arg_parser, check_mandatory_set_with_f)
{
    int mandatory_ok;
    const char *av[15] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    mandatory_ok = check_mandatory_set(15, av, 6, SERVER_OPTION);
    cr_assert_eq(mandatory_ok, 0);
}

Test(arg_parser, check_mandatory_set_incorrect, .description = "Port missing")
{
    int mandatory_ok;
    const char *av[11] = {"zappy", "-w", "30", "-y", "100", "-n", "toto",
        "titi", "-c", "2", NULL };

    mandatory_ok = check_mandatory_set(11, av, 4, SERVER_OPTION);
    cr_assert_eq(mandatory_ok, -1);
}

Test(arg_parser, get_nb_parameter)
{
    int nb_parameter;
    const char *av[13] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", NULL };

    nb_parameter = get_nb_parameter(13, av);
    cr_assert_eq(nb_parameter, 5);
}

Test(arg_parser, get_nb_parameter_with_f)
{
    int nb_parameter;
    const char *av[15] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    nb_parameter = get_nb_parameter(15, av);
    cr_assert_eq(nb_parameter, 6);
}

Test(arg_parser, is_param)
{
    int r_val;
    const char *av[15] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    r_val = is_param(av[1], &SERVER_OPTION[0].option);
    cr_assert(r_val != -1);
}

Test(arg_parser, is_param_false)
{
    int r_val;
    const char *av[15] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    r_val = is_param(av[0], &SERVER_OPTION[0].option);
    cr_assert(r_val == -1);
}

Test(arg_parser, get_arg)
{
    struct arg_s **args;
    char **teams;
    const char *av[13] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", NULL };

    args = get_zappy_args(13, av, SERVER_OPTION);
    if (args == NULL)
        exit(1);
    cr_assert_str_eq(args[0]->name, "-p");
    cr_assert_str_eq((char *)args[0]->value, "8888");
    cr_assert_str_eq(args[1]->name, "-w");
    cr_assert_str_eq((char *)args[1]->value, "30");
    cr_assert_str_eq(args[2]->name, "-y");
    cr_assert_str_eq((char *)args[2]->value, "100");
    cr_assert_str_eq(args[3]->name, "-n");
    cr_assert_eq(args[3]->nb_value, 2);
    teams = (char **)args[3]->value;
    cr_assert_str_eq(teams[0], "toto");
    cr_assert_str_eq(teams[1], "titi");
    cr_assert_str_eq(args[4]->name, "-c");
    cr_assert_str_eq((char *)args[4]->value, "2");
}

Test(arg_parser, get_arg_with_f)
{
    struct arg_s **args;
    char **teams;
    const char *av[15] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    args = get_zappy_args(15, av, SERVER_OPTION);
    if (args == NULL)
        exit(1);
    cr_assert_str_eq(args[0]->name, "-p");
    cr_assert_str_eq((char *)args[0]->value, "8888");
    cr_assert_str_eq(args[1]->name, "-w");
    cr_assert_str_eq((char *)args[1]->value, "30");
    cr_assert_str_eq(args[2]->name, "-y");
    cr_assert_str_eq((char *)args[2]->value, "100");
    cr_assert_str_eq(args[3]->name, "-n");
    cr_assert_eq(args[3]->nb_value, 2);
    teams = (char **)args[3]->value;
    cr_assert_str_eq(teams[0], "toto");
    cr_assert_str_eq(teams[1], "titi");
    cr_assert_str_eq(args[4]->name, "-c");
    cr_assert_str_eq((char *)args[4]->value, "2");
    cr_assert_str_eq(args[5]->name, "-f");
    cr_assert_str_eq((char *)args[5]->value, "200");

}

Test(arg_parser, get_arg_fail)
{
    struct arg_s **args;
    const char *av[13] = {"zappy", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    args = get_zappy_args(13, av, SERVER_OPTION);
    cr_assert(args == NULL);
}
