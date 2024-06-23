/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Parsing.cpp
*/

#include <cstring>
#include <iostream>

#include "Parsing.hpp"
#include "ArgumentHandling.hpp"


Parsing::Parsing()
: _port(""),
_machine("")
{
}

Parsing::~Parsing()
{
}

void Parsing::_validate_args() const
{
    if (_port.empty() || _machine.empty()) {
        throw Exception::ArgumentHandling("Missing arguments.");
    }
}

bool Parsing::_check_valid_port(const std::string &port)
{
    for (size_t i = 0; i < port.size(); ++i) {
        char c = port[i];
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}

void Parsing::help() const
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
}

void Parsing::parse_args(int ac, char **av)
{
    for (int i = 1; i < ac; ++i) {
        if (std::strcmp(av[i], "-p") == 0 && i + 1 < ac) {
            _port = av[++i];
            if (_check_valid_port(_port) != true)
                throw Exception::ArgumentHandling("Invalid port number.");
        } else if (std::strcmp(av[i], "-h") == 0 && i + 1 < ac) {
            _machine = av[++i];
        } else {
            throw Exception::ArgumentHandling("Invalid argument: " + std::string(av[i]));
        }
    }
    _validate_args();
}

void Parsing::print_args() const
{
    std::cout << "Port : " << _port << std::endl;
    std::cout << "Machine : " << _machine << std::endl;
}

const std::string &Parsing::get_machine() const
{
    return _machine;
}

const std::string &Parsing::get_port() const
{
    return _port;
}
