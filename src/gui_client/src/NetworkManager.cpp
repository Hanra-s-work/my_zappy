/*
** EPITECH PROJECT, 2024
** new
** File description:
** NetworkManager.cpp
*/

#include "NetworkManager.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

NetworkManager::NetworkManager(const std::string& host, const std::string& port)
    : socket(io_context) {
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket, resolver.resolve(host, port));
}

void NetworkManager::send(const std::string& message) {
    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}

std::string NetworkManager::receive() {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, "\n");
    return boost::asio::buffer_cast<const char*>(buffer.data());
}
