/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** Game.hpp
*/

#ifndef GAMELOOP_HPP_
    #define GAMELOOP_HPP_

    #include <memory>

    #include "GameState.hpp"
    #include "network/NetworkManager.hpp"

class GameLoop {
    public:
        GameLoop(const std::string &host, const std::string &port);
        ~GameLoop();

        void runGame();

    private:
        std::vector<std::string> _parseMessage(const std::string &msg);
        void _whichMessage(const std::vector<std::string> vec);
        void _retrieveInformations();

        std::unique_ptr<NetworkManager> _networkManager;
        std::unique_ptr<GameState> _gameState;
        // void processEvents();
        // void update(sf::Time deltaTime);
        // void render();

        // Graphic graphic;
        // Player player;
        // Resource resource;
        // Sound sound;

        // bool followPlayer;
};

#endif
