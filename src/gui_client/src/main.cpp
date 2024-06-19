/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** main.cpp
*/

#include "Graphic.hpp"
#include "Player.hpp"
#include "Game.hpp"

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
    Player player("asset/player_left.png", {700, 300}, {200, 300}, 100.0f, 0.3f);

    std::vector<std::pair<Direction, sf::Vector2f>> directions = {
        {Direction::Left, {200, 300}},
        {Direction::Right, {600, 300}},
        {Direction::Up, {600, 100}},
        {Direction::Down, {600, 500}}
    };
    size_t currentDirection = 0;

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
        graphic.handleInput();
        sf::Time elapsed = clock.restart();
        if (player.ReachedDestination() && currentDirection < directions.size() - 1) {
            currentDirection++;
            player.setDirection(directions[currentDirection].first, directions[currentDirection].second);
        }

        player.updateTime(elapsed);

        window.clear();
        resource.draw(window);
        player.draw(window);
        window.display();
    }
    return 0;
}
