/*
** EPITECH PROJECT, 2024
** new
** File description:
** NetworkManager.hpp
*/

#ifndef NETWORKMANAGER_HPP
    #define NETWORKMANAGER_HPP

    #include <iostream>
    #include <string>
    #include <boost/asio.hpp>

class NetworkManager
{
    public:
        NetworkManager(const std::string& host, const std::string& port);
        void send(const std::string& message);
        std::string receive();

    private:
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket;
};

#endif
