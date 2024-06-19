/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** NetworkClient.hpp
*/

#ifndef NETWORKCLIENT_HPP_
    #define NETWORKCLIENT_HPP_

    #include "INetwork.hpp"
    #include <SFML/Network.hpp>
    #include <thread>
    #include <atomic>

class NetworkClient : public INetwork
{
public:
    NetworkClient();
    ~NetworkClient();
    void connect(const std::string& ip, int port) override;
    void send(const std::string& message) override;
    void receive(std::function<void(const std::string&)> callback) override;

private:
    sf::TcpSocket _socket;
    std::thread _receiveThread;
    std::atomic<bool> _running;
    void receiveLoop(std::function<void(const std::string&)> callback);
};

#endif
