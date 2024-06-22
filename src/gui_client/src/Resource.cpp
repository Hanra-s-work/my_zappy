/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Resources
*/

#include "Resource.hpp"

Resource::Resource(const std::string &textureFile) : ISprite(textureFile), mapWidth(0), mapHeight(0)
{
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

    for (const auto &pair : resourceDensity) {
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

            materials.push_back({materialSprite, type});
        }
    }
}

void Resource::draw(sf::RenderWindow &window) const
{
    for (const auto &cellSprite : mapSprites) {
        window.draw(cellSprite);
    }

    for (const auto &material : materials) {
        window.draw(material.sprite);
    }
}

void Resource::addResourceAt(const std::string &type, int x, int y)
{
    if (materialTextures.find(type) == materialTextures.end()) {
        return;
    }

    sf::Sprite materialSprite;
    materialSprite.setTexture(materialTextures[type]);
    materialSprite.setPosition(x * 128.0f, y * 128.0f);

    materials.push_back({materialSprite, type});
}
