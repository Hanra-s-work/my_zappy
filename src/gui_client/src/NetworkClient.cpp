/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** INetwork.cpp
*/

#include "NetworkClient.hpp"
#include <thread>
#include <iostream>

NetworkClient::NetworkClient() : _running(false) {}

NetworkClient::~NetworkClient()
{
    _running = false;
    if (_receiveThread.joinable())
        _receiveThread.join();
}

void NetworkClient::connect(const std::string& ip, int port)
{
    if (_socket.connect(ip, port) != sf::Socket::Done)
    {
        throw std::runtime_error("Failed to connect to server");
    }
    _running = true;
}

void NetworkClient::send(const std::string& message)
{
    if (_socket.send(message.c_str(), message.size()) != sf::Socket::Done)
    {
        throw std::runtime_error("Failed to send message");
    }
}

void NetworkClient::receive(std::function<void(const std::string&)> callback)
{
    _receiveThread = std::thread(&NetworkClient::receiveLoop, this, callback);
}

void NetworkClient::receiveLoop(std::function<void(const std::string&)> callback)
{
    char data[100];
    std::size_t received;
    while (_running)
    {
        if (_socket.receive(data, sizeof(data), received) == sf::Socket::Done)
        {
            callback(std::string(data, received));
        }
    }
}
