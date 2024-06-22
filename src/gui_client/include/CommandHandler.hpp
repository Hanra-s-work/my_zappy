/*
** EPITECH PROJECT, 2023
** new
** File description:
** CommandHandler.hpp
*/

#ifndef COMMANDHANDLER_HPP
    #define COMMANDHANDLER_HPP

    #include <string>
    #include <iostream>
    #include "GameState.hpp"

class CommandHandler
{
    public:
        CommandHandler(GameState& gameState);
        void handleCommand(const std::string& command);

    private:
        GameState& gameState;
};

#endif
