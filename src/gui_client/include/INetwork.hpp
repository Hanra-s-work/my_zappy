/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** INetwork.hpp
*/

#ifndef INETWORK_HPP_
    #define INETWORK_HPP_

    #include <string>
    #include <functional>

class INetwork
{
public:
    virtual ~INetwork() = default;
    virtual void connect(const std::string& ip, int port) = 0;
    virtual void send(const std::string& message) = 0;
    virtual void receive(std::function<void(const std::string&)> callback) = 0;
};

#endif
