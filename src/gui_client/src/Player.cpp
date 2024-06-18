/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "Graphic.hpp"

Player::Player(const std::string &textureFile, const sf::Vector2f &startPosition, const sf::Vector2f &destPosition, float moveSpeed, float animationSpeed) : ISprite(textureFile)
{
    if (!_texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Error when loading texture");
    }
    _sprite.setTexture(_texture);
    _rect = sf::IntRect(0, 0, 48, 69);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(startPosition);

    _textures = {
        {Direction::Right, "asset/player_right.png"},
        {Direction::Left, "asset/player_left.png"},
        {Direction::Up, "asset/player_up.png"},
        {Direction::Down, "asset/player_down.png"},
    };
    _currentDir = Direction::Left;
    updateDirection();
}

void Player::setDirection(Direction dir, const sf::Vector2f &newDestPosition)
{
    _currentDir = dir;
    _destPosition = newDestPosition;
    updateDirection();

    if (!_texture.loadFromFile(_textures[_currentDir])) {
        throw std::runtime_error("Error when loading texture for direction");
    }
    _sprite.setTexture(_texture);
    _reachedDest = false;
}

void Player::updateDirection()
{
    sf::Vector2f directionVec = _destPosition - _sprite.getPosition();
    float distance = std::sqrt(directionVec.x * directionVec.x + directionVec.y * directionVec.y);
    _direction = directionVec / distance;
}

void Player::updateTime(sf::Time elapsed)
{
    if (!_reachedDest) {
        sf::Vector2f movement = _direction * _moveSpeed * elapsed.asSeconds();
        _sprite.move(movement);

        _elapsedTime += elapsed;
        if (_elapsedTime.asSeconds() > _animationSpeed) {
            _elapsedTime = sf::Time::Zero;
            _rect.left += _rect.width;
            if (_rect.left >= 350)
                _rect.left = 0;

            _sprite.setTextureRect(_rect);
        }
        if (std::abs(_sprite.getPosition().x - _destPosition.x) < 1.0f &&
            std::abs(_sprite.getPosition().y - _destPosition.y) < 1.0f) {
            _sprite.setPosition(_destPosition);
            _reachedDest = true;
        }
    }
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(_sprite);
}

bool Player::ReachedDestination() const
{
    return _reachedDest;
}
