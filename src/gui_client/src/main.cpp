/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** main.cpp
*/

#include "Graphic.hpp"
#include <vector>
// #include "Player.hpp"
// #include "Game.hpp"

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
    graphic.initWindow(1920, 1080, "My Zappy");
    Resource resource("asset/flower_grass.png");

    sf::Clock clock;
    sf::Vector2f randomStartPosition(static_cast<float>(std::rand() % (200 * 128)), static_cast<float>(std::rand() % (200 * 128)));
    Player player("asset/walk.png", randomStartPosition, 200.0f, 140.0f);

    bool followPlayer = false;

    resource.addMaterial("food", "asset/food.png");
    resource.addMaterial("linemate", "asset/linemate.png");
    resource.addMaterial("deraumere", "asset/deraumere.png");
    resource.addMaterial("sibur", "asset/sibur.png");
    resource.addMaterial("mendiane", "asset/mendiane.png");
    resource.addMaterial("phiras", "asset/phiras.png");
    resource.addMaterial("thystame", "asset/thystame.png");

    resource.generateMap(200, 200);
    resource.generateMaterials();
    graphic.setMapSize(resource.getMapWidth(), resource.getMapHeight());
    sf::RenderWindow &window = graphic.getWindow();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        graphic.handleInput(followPlayer, player.getPosition());
        player.handleInput();

        sf::Time elapsed = clock.restart();
        player.updateTime(elapsed);

        window.clear();
        resource.draw(window);
        player.draw(window);
        window.display();
    }
    return 0;
}
