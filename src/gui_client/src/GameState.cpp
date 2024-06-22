/*
** EPITECH PROJECT, 2024
** new
** File description:
** GameState.cpp
*/

#include "GameState.hpp"

std::string GameState::getMsz() const
{
    return _msz;
}

std::string GameState::getBct(int x, int y)
{
    if (x * 100 + y < _bct.size()) {
        return _bct.at(x * 100 + y);
    }
    return "";
}

std::string GameState::getMct() const
{
    return _mct;
}

std::string GameState::getTna()
{
    return _tna;
}

std::vector<std::string> GameState::getPpo()
{
    return _ppo;
}

std::vector<std::string> GameState::getPnw()
{
    return _pnw;
}

void GameState::addPlayer(const PlayerState& player)
{
    players.push_back(player);
}

std::vector<PlayerState> GameState::getPlayers() const
{
    return players;
}

void GameState::updatePlayerPosition(int id, int x, int y, int orientation)
{
    for (auto& player : players) {
        if (player.id == id) {
            player.x = x;
            player.y = y;
            player.orientation = orientation;
            break;
        }
    }
}
