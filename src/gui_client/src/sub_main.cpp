/*
** EPITECH PROJECT, 2023
** my_zappy [fed34_prox_vm]
** File description:
** sub_main.cpp
*/

#include <iostream>

#include "Parsing.hpp"
#include "Constants.hpp"
#include "game/GameLoop.hpp"
#include "ArgumentHandling.hpp"

int sub_main(int argc, char **argv)
{
    Parsing args_parsing;

    try {
        args_parsing.parse_args(argc, argv);
        args_parsing.print_args();
    } catch (const Exception::ArgumentHandling &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        args_parsing.help();
        return ERROR;
    }
    try {
        GameLoop gameLoop(args_parsing.get_machine(), args_parsing.get_port());
        gameLoop.runGame();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return 0;
}
