/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Exception.cpp
*/

#include "ArgumentHandling.hpp"

namespace Exception
{
    ArgumentHandling::ArgumentHandling(const std::string &msg) : _msg(msg)
    {}

    ArgumentHandling::~ArgumentHandling()
    {}

    const char *ArgumentHandling::what() const noexcept
    {
        return this->_msg.c_str();
    }
}
