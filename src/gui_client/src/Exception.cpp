/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Exception.cpp
*/

#include "Exception.hpp"

namespace Exception
{
    Exception::Exception(const std::string &msg) : _msg(msg)
    {}

    Exception::~Exception()
    {}

    const char *Exception::what() const noexcept
    {
        return this->_msg.c_str();
    }
}
