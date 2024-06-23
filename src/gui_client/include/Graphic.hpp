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

class Graphic
{
    public:
        Graphic();
        void initWindow(unsigned int width, unsigned int height, const std::string &title);
        sf::RenderWindow &getWindow();
        void handleInput(bool &followPlayer, const sf::Vector2f &playerPosition);
        void setMapSize(float width, float height);
        void zoomIn();
        void zoomOut();
        void setCameraOffset(const sf::Vector2f &offset);
        void updateView(float deltaTime);

    private:
        sf::RenderWindow window;
        sf::View view;
        float scrollSpeed;
        float mapWidth;
        float mapHeight;
        bool isZoomed;
        sf::Vector2f cameraOffset;
        sf::Vector2f targetCenter;
        const float smoothingFactor = 0.1f;
};

class ISprite
{
    public:
        ISprite(const std::string& textureFile);
        ~ISprite() = default;
        bool loadTexture(const std::string& textureFile);
        virtual void draw(sf::RenderWindow& wwindow) const = 0;

    protected:
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif // GRAPHIC_HPP_
