/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** main.cpp
*/

#include "Graphic.hpp"

/**
 * @brief This is the function the compiler calls to successfully compile the program
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
    Graphic graphic;
    graphic.initWindow(1920, 1080, "SFML Window");
    Player player("path/to/player/texture.png");
    Resource resource("asset/flower_grass.png");

    resource.addMaterial("food", "asset/food.png");
    resource.addMaterial("linemate", "asset/linemate.png");
    resource.addMaterial("deraumere", "asset/deraumere.png");
    resource.addMaterial("sibur", "asset/sibur.png");
    resource.addMaterial("mendiane", "asset/mendiane.png");
    resource.addMaterial("phiras", "asset/phiras.png");
    resource.addMaterial("thystame", "asset/thystame.png");

    resource.generateMap(20, 20);
    resource.generateMaterials();
    sf::RenderWindow &window = graphic.getWindow();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        resource.draw(window);
        player.draw(window);
        window.display();
    }
    return 0;
}
