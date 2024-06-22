/*
** EPITECH PROJECT, 2023
** new
** File description:
** CommandHandler.cpp
*/

#include <iostream>
#include <sstream>
#include "CommandHandler.hpp"

CommandHandler::CommandHandler(GameState& gameState)
: gameState(gameState)
{}

void CommandHandler::handleCommand(const std::string& command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "msz") {
        std::cout << "Msz : " << gameState.getMsz() << std::endl;
    } else if (cmd == "pnw") {
        PlayerState player;
        iss >> player.id >> player.x >> player.y >> player.orientation >> player.level >> player.teamName;
        gameState.addPlayer(player);
        std::cout << "New player added: " << player.id << std::endl;
    } else if (cmd == "ppo") {
        int id, x, y, orientation;
        iss >> id >> x >> y >> orientation;
        gameState.updatePlayerPosition(id, x, y, orientation);
        std::cout << "Player position updated: " << id << " (" << x << "," << y << ")" << std::endl;
    } else if (cmd == "mct") {
        std::cout << "Mct : " << gameState.getMct() << std::endl;
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}
