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

void Graphic::initWindow(unsigned int width, unsigned int height, const std::string &title)
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

            unsigned int x = std::rand() % mapWidth;
            unsigned int y = std::rand() % mapHeight;
            materialSprite.setPosition(x * 128.0f, y * 128.0f);

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
