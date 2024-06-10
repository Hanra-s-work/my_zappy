/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Exception.hpp
*/

#pragma once

#include <iostream>
#include <stdexcept>

namespace Exception
{
    class Exception : public std::exception
    {
        public:
            Exception(const std::string &msg);
            ~Exception();
            const char *what() const noexcept override;

        private:
            std::string _msg;
    };
}
