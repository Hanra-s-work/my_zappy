/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

Game::Game(const std::string& ip, int port)
    : player("asset/player_left.png", {700, 300}, {200, 300}, 100.0f, 0.3f),
    resource("asset/flower_grass.png"),
    running(true)
    // networkClient()
{
    graphic.initWindow(1920, 1080, "SFML Window");

    resource.addMaterial("food", "asset/food.png");
    resource.addMaterial("linemate", "asset/linemate.png");
    resource.addMaterial("deraumere", "asset/deraumere.png");
    resource.addMaterial("sibur", "asset/sibur.png");
    resource.addMaterial("mendiane", "asset/mendiane.png");
    resource.addMaterial("phiras", "asset/phiras.png");
    resource.addMaterial("thystame", "asset/thystame.png");

    resource.generateMap(20, 20);
    resource.generateMaterials();

    networkClient.connect(ip, port);
    networkClient.receive([this](const std::string& message)
    {
        handleServerMessage(message);
    });
}

Game::~Game()
{
    running = false;
}

void Game::handleServerMessage(const std::string& message)
{
    std::cout << "Received message from server: " << message << std::endl;

    std::istringstream iss(message);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    if (tokens.empty()) {
        return;
    }
    const std::string &command = tokens[0];

    if (command == "player_move") {
        if (tokens.size() != 4) {
            std::cerr << "Invalid player move command" << std::endl;
            return;
        }
        int playerId = std::stoi(tokens[1]);
        float x = std::stof(tokens[2]);
        float y = std::stof(tokens[3]);

        player.setPosition({x, y});
    } else if (command == "add_resource") {
        if (tokens.size() != 4) {
            std::cerr << "Invalid player move command" << std::endl;
            return;
        }
        const std::string& resourceType = tokens[1];
        int x = std::stoi(tokens[2]);
        int y = std::stoi(tokens[3]);

        resource.addResourceAt(resourceType, x, y);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}

void Game::run()
{
    sf::RenderWindow &window = graphic.getWindow();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        resource.draw(window);
        player.draw(window);
        window.display();
    }
}
