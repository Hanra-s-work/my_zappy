/*
** EPITECH PROJECT, 2023
** my_zappy [fed34_prox_vm]
** File description:
** sub_main.cpp
*/

#include <iostream>
#include "Parsing.hpp"
#include "ArgumentHandling.hpp"

int sub_main(int argc, char **argv)
{
    Gui::Parsing p;

    try {
        if (p.parse_args(argc, argv) != true) {
            p.help();
            return 84;
        }

        if (p.validate_args() != true) {
            p.help();
            return 84;
        }

        p.print_args();
    } catch (const Exception::ArgumentHandling &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        p.help();
        return 84;
    }
    return 0;
}
