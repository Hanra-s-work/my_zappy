/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include <SFML/Graphics.hpp>

class Graphic
{
    public:
        Graphic();
        void initWindow(int width, int height, const std::string &title);
        sf::RenderWindow &getWindow();
    private:
        sf::RenderWindow window;
};

class ISprite
{
    public:
        ISprite(const std::string &textureFile);
        bool loadTexture(const std::string &textureFile);
        virtual void draw(sf::RenderWindow &window) const = 0;
    protected:
        sf::Sprite sprite;
        sf::Texture texture;
};

class Player : public ISprite
{
    public:
        Player(const std::string &textureFile);
        void draw(sf::RenderWindow &window) const override;
};

class Resource : public ISprite
{
    public:
        Resource(const std::string &textureFile);
        void draw(sf::RenderWindow &window) const override;
};

#endif /* !GRAPHIC_HPP_ */
