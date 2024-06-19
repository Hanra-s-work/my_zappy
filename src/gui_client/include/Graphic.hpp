/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

class Graphic
{
    public:
        Graphic();
        void initWindow(unsigned int width, unsigned int height, const std::string& title);
        sf::RenderWindow& getWindow();
        void handleInput();
        void setMapSize(float width, float height);

    private:
        sf::RenderWindow window;
        sf::View view;
        float scrollSpeed;
        float mapWidth;
        float mapHeight;
};

class ISprite
{
    public:
        ISprite(const std::string& textureFile);
        bool loadTexture(const std::string& textureFile);
        virtual void draw(sf::RenderWindow& window) const = 0;

    protected:
        sf::Sprite sprite;
        sf::Texture texture;
};

// class Player : public ISprite
// {
//     public:
//         Player(const std::string& textureFile);
//         void draw(sf::RenderWindow& window) const override;
// };

struct Material
{
    sf::Sprite sprite;
    std::string type;
};

class Resource : public ISprite
{
    public:
        Resource(const std::string& textureFile);
        void generateMap(unsigned int width, unsigned int height);
        void addMaterial(const std::string& type, const std::string& textureFile);
        void generateMaterials();
        void draw(sf::RenderWindow& window) const override;

        unsigned int getMapWidth() const;
        unsigned int getMapHeight() const;

        void addResourceAt(const std::string &type, int x, int y);

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
            {"thystame", 0.05}
        };
};

#endif /* !GRAPHIC_HPP_ */
