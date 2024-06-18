/*
** EPITECH PROJECT, 10024
** my_zappy
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
    view.setCenter(sf::Vector2f(width / 2.0f, height / 2.0f));
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

void Graphic::handleInput()
{
    const float deltaTime = 1.0f / 60.0f;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f viewMove(0.0f, 0.0f);

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

    sf::Vector2f newCenter = view.getCenter() + viewMove;
    sf::Vector2f halfSize = view.getSize() / 2.0f;

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

Player::Player(const std::string &textureFile) : ISprite(textureFile)
{
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

Resource::Resource(const std::string &textureFile) : ISprite(textureFile), mapWidth(0), mapHeight(0)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Resource::generateMap(unsigned int width, unsigned int height)
{
    mapWidth = width;
    mapHeight = height;
    mapSprites.clear();

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            sf::Sprite cellSprite = sprite;
            cellSprite.setPosition(x * 128.0f, y * 128.0f);
            mapSprites.push_back(cellSprite);
        }
    }
}

unsigned int Resource::getMapWidth() const
{
    return mapWidth * 128;
}

unsigned int Resource::getMapHeight() const
{
    return mapHeight * 128;
}

void Resource::addMaterial(const std::string &type, const std::string &textureFile)
{
    sf::Texture texture;
    if (!texture.loadFromFile(textureFile)) {
        return;
    }
    materialTextures[type] = texture;
}

void Resource::generateMaterials()
{
    materials.clear();

    unsigned int totalCells = mapWidth * mapHeight;

    for (const auto& pair : resourceDensity) {
        const std::string &type = pair.first;
        float density = pair.second;
        unsigned int count = static_cast<unsigned int>(totalCells * density);
        for (unsigned int i = 0; i < count; ++i) {
            if (materialTextures.find(type) == materialTextures.end()) {
                continue;
            }
            sf::Sprite materialSprite;
            materialSprite.setTexture(materialTextures[type]);
            float x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (mapWidth - 1) * 128.0f;
            float y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (mapHeight - 1) * 128.0f;
            materialSprite.setPosition(x, y);

            materials.push_back({ materialSprite, type });
        }
    }
}

void Resource::draw(sf::RenderWindow &window) const
{
    for (const auto& cellSprite : mapSprites) {
        window.draw(cellSprite);
    }

    for (const auto& material : materials) {
        window.draw(material.sprite);
    }
}
