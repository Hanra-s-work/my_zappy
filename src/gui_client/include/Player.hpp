/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include "Graphic.hpp"
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <cmath>
    #include <unordered_map>

enum class Direction
{
    Right,
    Left,
    Up,
    Down
};

class Player : public ISprite
{
    public:
        Player(const std::string &textureFile, const sf::Vector2f &startPosition, const sf::Vector2f &destPosition, float moveSpeed, float animationSpeed);
        void setDirection(Direction dir, const sf::Vector2f &newDestPosition);
        void updateTime(sf::Time elapsed);
        void draw(sf::RenderWindow &window) const override;
        bool ReachedDestination() const;
        void setPosition(const sf::Vector2f &position);

    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::IntRect _rect;
        sf::Vector2f _direction;
        sf::Vector2f _destPosition;
        float _moveSpeed;
        float _animationSpeed;
        bool _reachedDest;
        sf::Time _elapsedTime;
        void updateDirection();
        Direction _currentDir;
        std::unordered_map<Direction, std::string> _textures;
};

#endif
