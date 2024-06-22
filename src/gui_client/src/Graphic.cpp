/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Graphic
*/

#include "Graphic.hpp"

Graphic::Graphic() : scrollSpeed(500.0f), mapWidth(0), mapHeight(0)
{
}

void Graphic::initWindow(unsigned int width, unsigned int height, const std::string &title)
{
    window.create(sf::VideoMode(width, height), title);
    view.setSize(sf::Vector2f(width, height));
    view.setCenter(sf::Vector2f(width / 1.0f, height / 1.0f));
    window.setView(view);
}

sf::RenderWindow &Graphic::getWindow()
{
    return window;
}

void Graphic::setMapSize(float width, float height)
{
    mapWidth = width;
    mapHeight = height;
}

void Graphic::handleInput(bool &followPlayer, const sf::Vector2f &playerPosition)
{
    const float deltaTime = 1.0f / 60.0f;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f viewMove(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        scrollSpeed += 50.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) || sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
        scrollSpeed -= 50.0f;
        if (scrollSpeed < 0) {
            scrollSpeed = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        followPlayer = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        followPlayer = false;
    }

    if (!followPlayer) {
        if (mousePosition.x <= 100) {
            viewMove.x = -scrollSpeed * deltaTime;
        }
        if (mousePosition.x >= windowSize.x - 100) {
            viewMove.x = scrollSpeed * deltaTime;
        }
        if (mousePosition.y <= 100) {
            viewMove.y = -scrollSpeed * deltaTime;
        }
        if (mousePosition.y >= windowSize.y - 100) {
            viewMove.y = scrollSpeed * deltaTime;
        }
    }
    sf::Vector2f newCenter = followPlayer ? playerPosition : view.getCenter() + viewMove;
    sf::Vector2f halfSize = view.getSize() / 1.0f;
    if (newCenter.x - halfSize.x < 0) {
        newCenter.x = halfSize.x;
    }
    if (newCenter.x + halfSize.x > mapWidth) {
        newCenter.x = mapWidth - halfSize.x;
    }
    if (newCenter.y - halfSize.y < 0) {
        newCenter.y = halfSize.y;
    }
    if (newCenter.y + halfSize.y > mapHeight) {
        newCenter.y = mapHeight - halfSize.y;
    }
    view.setCenter(newCenter);
    window.setView(view);
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
