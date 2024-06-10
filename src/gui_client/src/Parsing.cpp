/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Parsing.cpp
*/

#include <cstring>
#include "Parsing.hpp"
#include "ArgumentHandling.hpp"

namespace Gui
{
    Parsing::Parsing() : _port(""), _machine("")
    {}

    void Parsing::help() const
    {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    }

    bool Parsing::parse_args(int ac, char **av)
    {
        for (int i = 1; i < ac; ++i) {
            if (std::strcmp(av[i], "-p") == 0 && i + 1 < ac) {
                _port = av[++i];
                if (check_valid_port(_port) != true)
                    throw Exception::ArgumentHandling("Invalid port number.");
            } else if (std::strcmp(av[i], "-h") == 0 && i + 1 < ac) {
                _machine = av[++i];
            } else {
                throw Exception::ArgumentHandling("Invalid argument: " + std::string(av[i]));
            }
        }
        return true;
    }

    bool Parsing::validate_args() const
    {
        if (_port.empty() || _machine.empty()) {
            throw Exception::ArgumentHandling("Missing arguments.");
        }
        return true;
    }

    void Parsing::print_args() const
    {
        std::cout << "Port : " << _port << std::endl;
        std::cout << "Machine : " << _machine << std::endl;
    }

    bool Parsing::check_valid_port(const std::string &port)
    {
        char c = NULL;

        for (size_t i = 0; i < port.size(); ++i) {
            c = port[i];
            if (std::isdigit(c) == 0)
                return false;
        }
        return true;
    }
}
