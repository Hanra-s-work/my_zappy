/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "Parsing.hpp"
#include "NetworkManager.hpp"
#include "CommandHandler.hpp"
#include "GameState.hpp"

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
    Resource resource("asset/pictures/resources/flower_grass.png");

    Sound sound;
    sound.loadMusic("asset/sound/C418 - Moog City.ogg");
    sound.playMusic();
    sound.loadSound("footsteps", "asset/sound/footstep.ogg");

    sf::Clock clock;
    sf::Vector2f randomStartPosition(static_cast<float>(std::rand() % (200 * 128)), static_cast<float>(std::rand() % (200 * 128)));
    Team team(1, "asset/pictures/character/walk.png", randomStartPosition, 120.0f, 6.0f, sound);

    bool followPlayer = false;

    // Parsing parsing;
    // GameState gameState;
    // NetworkManager networkManager("127.0.0.1", "4242");
    // networkManager.send("GRAPHIC");
    // CommandHandler commandHandler(gameState);

    resource.addMaterial("food", "asset/pictures/resources/food.png");
    resource.addMaterial("linemate", "asset/pictures/resources/linemate.png");
    resource.addMaterial("deraumere", "asset/pictures/resources/deraumere.png");
    resource.addMaterial("sibur", "asset/pictures/resources/sibur.png");
    resource.addMaterial("mendiane", "asset/pictures/resources/mendiane.png");
    resource.addMaterial("phiras", "asset/pictures/resources/phiras.png");
    resource.addMaterial("thystame", "asset/pictures/resources/thystame.png");

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
        graphic.handleInput(followPlayer, team.getPosition());
        team.handleInput();

        sf::Time elapsed = clock.restart();
        team.updateTime(elapsed);
        graphic.updateView(elapsed.asSeconds());

        // std::string command = networkManager.receive();
        // commandHandler.handleCommand(command);

        window.clear();
        resource.draw(window);
        team.draw(window);
        window.display();
    }
    return 0;
}

/*
rajouter la condition "si le player passe sur une ressource alors elle disparait et réaparait ailleurs"
rajouter des bordures sur la map au extremité pour ne pas laissé passer le player
rajouter un pitit zoom quand on passe sur la cam d'un player
gérer le volume de la musique avec + et -
gérer le zoom de la cam libre avec + et -
*/
