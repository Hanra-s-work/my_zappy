/*
** EPITECH PROJECT, 2023
** my_zappy [fed34_prox_vm]
** File description:
** sub_main.cpp
*/

#include <iostream>
#include "Parsing.hpp"

int sub_main(int argc, char **argv)
{
    Gui::Parsing p;

    if (p.parse_args(argc, argv) != true) {
        p.help();
        return 84;
    }

    if (p.validate_args() != true) {
        p.help();
        return 84;
    }

    p.print_args();
    return 0;
}
