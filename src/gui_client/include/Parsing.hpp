/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Parsing.hpp
*/

#ifndef PARSING_HPP
    #define PARSING_HPP

class Parsing {
    public:
        Parsing();
        ~Parsing();

        void help() const;
        void parse_args(int ac, char **av);
        void print_args() const;
        const std::string &get_machine() const;
        const std::string &get_port() const;

    private:
        void _validate_args() const;
        bool _check_valid_port(const std::string &port);

        std::string _port;
        std::string _machine;
};

#endif
