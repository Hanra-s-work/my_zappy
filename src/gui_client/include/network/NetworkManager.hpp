/*
** EPITECH PROJECT, 2024
** new
** File description:
** NetworkManager.hpp
*/

#ifndef NETWORKMANAGER_HPP
    #define NETWORKMANAGER_HPP

    #include <string>
    #include <iostream>
    #include <boost/asio.hpp>

class NetworkManager {
    public:
        NetworkManager(const std::string &host, const std::string &port);
        ~NetworkManager();

        void send(const std::string &message, int timeout);
        std::string receive(int timeout);

    private:
        boost::asio::io_context _io_context;
        boost::asio::ip::tcp::socket _socket;
};

#endif
