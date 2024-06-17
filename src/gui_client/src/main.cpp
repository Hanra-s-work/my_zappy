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
    Resource resource("path/to/resource/texture.png");
    sf::RenderWindow &window = graphic.getWindow();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        player.draw(window);
        resource.draw(window);
        window.display();
    }

    return 0;
}
