/*
** EPITECH PROJECT, 2024
** new
** File description:
** NetworkManager.cpp
*/

#include <thread>
#include <chrono>
#include <vector>
#include <istream>
#include <stdexcept>
#include <boost/asio.hpp>

#include "Constants.hpp"
#include "network/NetworkManager.hpp"

NetworkManager::NetworkManager(const std::string &host, const std::string &port)
: _socket(_io_context)
{
    try {
        boost::asio::ip::tcp::resolver resolver(_io_context);
        boost::asio::connect(_socket, resolver.resolve(host, port));
    } catch (boost::system::system_error &e) {
        throw std::runtime_error(e.what());
    }
}

NetworkManager::~NetworkManager()
{
    boost::system::error_code ec;

    if (_socket.is_open()) {
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        _socket.close(ec);
        if (ec) {
            std::cerr << "Error closing socket: " << ec.message() << std::endl;
        }
    }
}

void NetworkManager::send(const std::string &message, int timeout)
{
    try {
        boost::asio::write(_socket, boost::asio::buffer(message + "\n"));
    } catch (boost::system::system_error &e) {
        throw std::runtime_error(e.what());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

std::string NetworkManager::receive(int timeout)
{
    boost::asio::streambuf buffer;
    boost::system::error_code ec;
    std::size_t bytes_available = _socket.available(ec);

    if (bytes_available == 0) {
            return "";
    }
    if (ec) {
        throw std::runtime_error("Error checking available bytes: " + ec.message());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    try {
        boost::asio::read_until(_socket, buffer, "\n");
    } catch (boost::system::system_error &e) {
        throw std::runtime_error(e.what());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    std::cout << boost::asio::buffer_cast<const char *>(buffer.data()) << std::endl;
    return boost::asio::buffer_cast<const char *>(buffer.data());
}
