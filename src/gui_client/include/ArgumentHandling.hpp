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
    class ArgumentHandling : public std::exception
    {
        public:
            ArgumentHandling(const std::string &msg);
            ~ArgumentHandling();
            const char *what() const noexcept override;

        private:
            std::string _msg;
    };
}
