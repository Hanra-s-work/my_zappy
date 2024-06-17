/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Graphic
*/

#include "Graphic.hpp"

Graphic::Graphic()
{
}

void Graphic::initWindow(int width, int height, const std::string &title)
{
    window.create(sf::VideoMode(width, height), title);
}

sf::RenderWindow &Graphic::getWindow()
{
    return window;
}

ISprite::ISprite(const std::string &textureFile)
{
    loadTexture(textureFile);
}

bool ISprite::loadTexture(const std::string &textureFile)
{
    if (!texture.loadFromFile(textureFile)) {
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

Player::Player(const std::string &textureFile) : ISprite(textureFile)
{
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

Resource::Resource(const std::string &textureFile) : ISprite(textureFile)
{
}

void Resource::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}
