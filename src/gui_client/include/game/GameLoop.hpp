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
    #include "graphic/Graphic.hpp"
    #include "graphic/Player.hpp"
    #include "graphic/Resource.hpp"
    #include "graphic/Sound.hpp"

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
        std::unique_ptr<Graphic> graphic;
        std::unique_ptr<Resource> resource;
        std::unique_ptr<Sound> sound;
        std::unique_ptr<VolumeVisualizer> volumeVisualizer;
        std::vector<std::unique_ptr<Team>> teams;
        sf::Event event;
        sf::Clock clock;
        bool followPlayer;
};

#endif
