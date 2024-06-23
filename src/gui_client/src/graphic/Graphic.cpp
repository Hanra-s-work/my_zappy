/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Graphic
*/

#include "graphic/Graphic.hpp"

Graphic::Graphic() : scrollSpeed(500.0f), mapWidth(0), mapHeight(0), isZoomed(false), cameraOffset(-120.0f, -120.0f), targetCenter(-120.0f, -120.0f)
{
}

Graphic::~Graphic()
{
}

void Graphic::initWindow(unsigned int width, unsigned int height, const std::string &title)
{
    window.create(sf::VideoMode(width, height), title);
    view.setSize(sf::Vector2f(width, height));
    view.setCenter(sf::Vector2f(width / 2.0f, height / 2.0f));
    targetCenter = view.getCenter();
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

void Graphic::zoomIn()
{
    view.zoom(0.5f);
    isZoomed = true;
    window.setView(view);
}

void Graphic::zoomOut()
{
    view.zoom(2.0f);
    isZoomed = false;
    window.setView(view);
}

void Graphic::setCameraOffset(const sf::Vector2f &offset)
{
    cameraOffset = offset;
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
        if (!isZoomed) {
            zoomIn();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        followPlayer = false;
        if (isZoomed) {
            zoomOut();
        }
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

    sf::Vector2f adjustedPlayerPosition = playerPosition - cameraOffset;
    targetCenter = followPlayer ? adjustedPlayerPosition : view.getCenter() + viewMove;
    sf::Vector2f halfSize = view.getSize() / 2.0f;
    if (targetCenter.x - halfSize.x < 0) {
        targetCenter.x = halfSize.x;
    }
    if (targetCenter.x + halfSize.x > mapWidth) {
        targetCenter.x = mapWidth - halfSize.x;
    }
    if (targetCenter.y - halfSize.y < 0) {
        targetCenter.y = halfSize.y;
    }
    if (targetCenter.y + halfSize.y > mapHeight) {
        targetCenter.y = mapHeight - halfSize.y;
    }
}

void Graphic::updateView(float deltaTime)
{
    sf::Vector2f currentCenter = view.getCenter();
    sf::Vector2f newCenter = currentCenter + smoothingFactor * (targetCenter - currentCenter);
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
