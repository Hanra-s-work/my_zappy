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
    #include <iostream>
    #include <cmath>
    #include <unordered_map>

class Graphic
{
    public:
        Graphic();
        void initWindow(unsigned int width, unsigned int height, const std::string& title);
        sf::RenderWindow& getWindow();
        void handleInput(bool& followPlayer, const sf::Vector2f& playerPosition);
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

enum class Direction
{
    Right,
    Left,
    Up,
    Down
};

class Player : public ISprite
{
    public:
        Player(const std::string &textureFile, const sf::Vector2f &startPosition, float moveSpeed, float animationSpeed);
        void handleInput();
        void updateTime(sf::Time elapsed);
        void draw(sf::RenderWindow &window) const override;
        void setPosition(const sf::Vector2f &position);
        sf::Vector2f getPosition() const;

    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::IntRect _rect;
        sf::Vector2f _direction;
        sf::Vector2f _destPosition;
        float _moveSpeed;
        float _animationSpeed;
        bool _reachedDest;
        sf::Time _elapsedTime;
        void updateDirection();
        void updateAnimation();
        Direction _currentDir;
};

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
