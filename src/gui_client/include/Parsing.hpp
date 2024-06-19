/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Parsing.hpp
*/

#pragma once

#include <iostream>

    class Parsing {
        public:
            Parsing();
            void help() const;
            bool parse_args(int ac, char **av);
            bool validate_args() const;
            void print_args() const;
            const std::string& get_machine() const;
            const std::string& get_port() const;

        private:
            std::string _port;
            std::string _machine;
            bool check_valid_port(const std::string &port);
    };
