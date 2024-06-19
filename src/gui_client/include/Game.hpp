/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** Game.hpp
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include "Graphic.hpp"
    #include "Player.hpp"
    #include "NetworkClient.hpp"
    #include <string>

class Game
{
public:
    Game(const std::string &ip, int port);
    ~Game();
    void run();

private:
    Graphic graphic;
    Player player;
    Resource resource;
    NetworkClient networkClient;
    std::atomic<bool> running;

    void handleServerMessage(const std::string &message);
};

#endif
