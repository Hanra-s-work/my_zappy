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
    int nb_mandatory = get_nb_mandatory_option();

    cr_assert_eq(nb_mandatory, 5);
}

Test(arg_parser, check_mandatory_set)
{
    int mandatory_ok;
    const char *av[13] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", NULL};

    mandatory_ok = check_mandatory_set(13, av);
    cr_assert_eq(mandatory_ok, 0);
}

Test(arg_parser, check_mandatory_set_with_f)
{
    int mandatory_ok;
    const char *av[15] = {"zappy", "-p", "8888", "-w", "30", "-y", "100", "-n",
        "toto", "titi", "-c", "2", "-f", "200", NULL };

    mandatory_ok = check_mandatory_set(15, av);
    cr_assert_eq(mandatory_ok, 0);
}

Test(arg_parser, check_mandatory_set_incorrect, .description = "Port missing")
{
    int mandatory_ok;
    const char *av[11] = {"zappy", "-w", "30", "-y", "100", "-n", "toto",
        "titi", "-c", "2", NULL };

    mandatory_ok = check_mandatory_set(11, av);
    cr_assert_eq(mandatory_ok, -1);
}
