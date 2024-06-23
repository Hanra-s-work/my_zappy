/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include "Graphic.hpp"
#include "Sound.hpp"
#include "game/GameState.hpp"

enum class Direction
{
    Idle,
    Up,
    Right,
    Down,
    Left
};

struct PlayerState;

class Player : public ISprite
{
    public:
        Player(const std::string &textureFile, const sf::Vector2f &startPosition, float moveSpeed, float animationSpeed, std::unique_ptr<Sound> &sound);
        void handleInput();
        void updateTime(sf::Time elapsed);
        void draw(sf::RenderWindow &window) const override;
        void setPosition(const sf::Vector2f &position);
        sf::Vector2f getPosition() const;
        void zoomIn(sf::RenderWindow &window);
        void zoomOut(sf::RenderWindow &window);
        void setView(sf::RenderWindow &window);

        sf::FloatRect getPlayerBounds() const;

    protected:
        sf::Texture _texture;
        sf::Texture _idleTexture;
        sf::Sprite _sprite;
        sf::IntRect _rect;
        sf::Vector2f _direction;
        sf::Vector2f _destPosition;
        float _moveSpeed;
        float _animationSpeed;
        bool _reachedDest;
        bool _usingIdleTexture = true;
        sf::Time _elapsedTime;
        Direction _currentDir;
        Direction _lastDir;
        std::unique_ptr<Sound> &_sound;
        bool _isZoomed = false;

        void updateDirection();
        void updateAnimation();
        void updateIdlePose();
};

class Team : public Player
{
    public:
        Team(int index, const std::string &textureFile, const sf::Vector2f &startPosition, float moveSpeed, float animationSpeed, std::unique_ptr<Sound> &sound);
        ~Team();
        void performIncantation();
        int getIndex() const;
        void spawnEgg();
        void hatchEgg();
        void draw(sf::RenderWindow &window) const override;
        void updatePosition(std::vector<PlayerState> states);

    private:
        int _index;
        std::vector<sf::Sprite> _eggs;
        sf::Texture _eggTexture;
        sf::Sprite _sprite;
        sf::Time _incantationTime;
        bool _incantationActive;
};

#endif // PLAYER_HPP_
