/*
** EPITECH PROJECT, 2024
** gui_client
** File description:
** Resources
*/

#ifndef RESOURCE_HPP_
    #define RESOURCE_HPP_

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>
    #include <map>

    #include "Graphic.hpp"

struct Material
{
    sf::Sprite sprite;
    std::string type;
};

class Resource : public ISprite
{
    public:
        Resource(const std::string &textureFile);
        ~Resource();
        void generateMap(unsigned int width, unsigned int height);
        void addMaterial(const std::string &type, const std::string &textureFile);
        void generateMaterials();
        void draw(sf::RenderWindow &window) const override;

        unsigned int getMapWidth() const;
        unsigned int getMapHeight() const;

        void addResourceAt(const std::string &type, int x, int y);
        // bool checkCollision(const sf::Vector2f &playerPosition);

    private:
        std::vector<sf::Sprite> mapSprites;
        std::vector<Material> materials;
        std::map<std::string, sf::Texture> materialTextures;
        unsigned int mapWidth;
        unsigned int mapHeight;

        std::map<std::string, float> resourceDensity = {
            {"food", 0.5},
            {"linemate", 0.3},
            {"deraumere", 0.15},
            {"sibur", 0.1},
            {"mendiane", 0.1},
            {"phiras", 0.08},
            {"thystame", 0.05}};
};

#endif // RESOURCE_HPP_
