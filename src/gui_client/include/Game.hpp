/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** Game.hpp
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <SFML/Graphics.hpp>
    #include "Graphic.hpp"
    #include "Player.hpp"
    #include "Resource.hpp"
    #include "Sound.hpp"

class Game
{
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        Graphic graphic;
        Player player;
        Resource resource;
        Sound sound;

        bool followPlayer;
};

#endif
