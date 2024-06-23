/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Player.cpp
*/

#include <iostream>
#include "graphic/Player.hpp"

Player::Player(const std::string &textureFile, const sf::Vector2f &startPosition, float moveSpeed, float animationSpeed, Sound &sound)
    : ISprite(textureFile), _direction(0, 0), _destPosition(startPosition), _moveSpeed(moveSpeed), _animationSpeed(animationSpeed), _reachedDest(false), _sound(sound)
{
    if (!_texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture");
    }
    if (!_idleTexture.loadFromFile("asset/pictures/character/idle.png")) {
        throw std::runtime_error("Failed to load idle texture");
    }
    _sprite.setTexture(_texture);
    _rect = sf::IntRect(0, 0, 80, 80);
    _sprite.setTextureRect(_rect);
    _sprite.setPosition(startPosition);
    _sprite.setScale(3.0f, 3.0f);
}

void Player::handleInput()
{
    sf::Vector2f oldDirection = _direction;
    _direction = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        _direction.y = -1;
        _currentDir = Direction::Up;
        _rect.top = 240;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _direction.y = 1;
        _currentDir = Direction::Down;
        _rect.top = 160;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        _direction.x = -1;
        _currentDir = Direction::Left;
        _rect.top = 80;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _direction.x = 1;
        _currentDir = Direction::Right;
        _rect.top = 0;
    } else {
        _currentDir = Direction::Idle;
    }
    if (_direction != sf::Vector2f(0, 0)) {
        if (oldDirection == sf::Vector2f(0, 0)) {
            _sound.playSound("footsteps", true);
        }
        _lastDir = _currentDir;
    } else {
        _sound.stopSound("footsteps");
    }
}

void Player::updateTime(sf::Time elapsed)
{
    _elapsedTime += elapsed;
    if (_elapsedTime.asSeconds() > 0.5f / _animationSpeed) {
        if (_currentDir != Direction::Idle) {
            _sprite.move(_direction * _moveSpeed * _elapsedTime.asSeconds());
            updateAnimation();
            if (_usingIdleTexture) {
                _sprite.setTexture(_texture);
                _usingIdleTexture = false;
            }
        } else {
            updateIdlePose();
        }
        _elapsedTime = sf::Time::Zero;
    }
}

void Player::updateAnimation()
{
    _rect.left += 80;
    if (_rect.left >= _texture.getSize().x) {
        _rect.left = 0;
    }
    _sprite.setTextureRect(_rect);
}

void Player::updateIdlePose()
{
    if (!_usingIdleTexture) {
        _sprite.setTexture(_idleTexture);
        _usingIdleTexture = true;
    }
    _sprite.setTexture(_idleTexture);
    switch (_lastDir) {
        case Direction::Up:
            _rect.top = 240;
            break;
        case Direction::Down:
            _rect.top = 160;
            break;
        case Direction::Left:
            _rect.top = 80;
            break;
        case Direction::Right:
        case Direction::Idle:
        default:
            _rect.top = 0;
            break;
    }
    _rect.left += 80;
    if (_rect.left >= _idleTexture.getSize().x) {
        _rect.left = 0;
    }
    _sprite.setTextureRect(_rect);
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(_sprite);
}

void Player::setPosition(const sf::Vector2f &position)
{
    _sprite.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return _sprite.getPosition();
}

void Player::zoomIn(sf::RenderWindow &window)
{
    sf::View view = window.getView();
    view.zoom(0.5f);
    window.setView(view);
    _isZoomed = true;
}

void Player::zoomOut(sf::RenderWindow &window)
{
    sf::View view = window.getView();
    view.zoom(2.0f);
    window.setView(view);
    _isZoomed = false;
}

void Player::setView(sf::RenderWindow &window)
{
    sf::View view = window.getView();
    view.setCenter(_sprite.getPosition());
    window.setView(view);
}

Team::Team(int index, const std::string &textureFile, const sf::Vector2f &startPosition, float moveSpeed, float animationSpeed, Sound &sound)
: Player(textureFile, startPosition, moveSpeed, animationSpeed, sound), _index(index), _incantationActive(false)
{
}

void Team::performIncantation()
{
    _incantationActive = true;
    _incantationTime = sf::Time::Zero;
}

void Team::spawnEgg()
{
    sf::Sprite eggSprite;
    eggSprite.setTexture(_eggTexture);
    eggSprite.setPosition(_sprite.getPosition());
    _eggs.push_back(eggSprite);
}

void Team::hatchEgg()
{
    if (!_eggs.empty()) {
        _eggs.erase(_eggs.begin());
    }
}

void Team::draw(sf::RenderWindow &window) const
{
    Player::draw(window);
    for (const auto& egg : _eggs) {
        window.draw(egg);
    }
}

sf::FloatRect Player::getPlayerBounds() const
{
    return _sprite.getGlobalBounds();
}
