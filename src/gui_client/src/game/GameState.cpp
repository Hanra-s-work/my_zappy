/*
** EPITECH PROJECT, 2024
** new
** File description:
** GameState.cpp
*/

#include <iostream>
#include <algorithm>

#include "game/GameLoop.hpp"

GameState::GameState()
{
}

GameState::~GameState()
{
}

std::vector<PlayerState> GameState::getPlayers() const
{
    return _players;
}

std::vector<Tile> GameState::getTiles() const
{
    return _tiles;
}

std::pair<int, int> GameState::getMapSize() const
{
    return _mapSize;
}

std::vector<std::string> GameState::getTeamsName() const
{
    return _teamsName;
}

PlayerState GameState::getSinglePlayer(int id) const
{
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i].id == id) {
            return _players[i];
        }
    }
    throw std::runtime_error("Player not found with id: " + std::to_string(id));
}

Tile GameState::getSingleTile(int x, int y) const
{
    for (std::size_t i = 0; i < _tiles.size(); i++) {
        if (_tiles[i].x == x && _tiles[i].y == y) {
            return _tiles[i];
        }
    }
    throw std::runtime_error("Tile " + std::to_string(x) + " " + std::to_string(y) + " not found");
}

void GameState::setMapSize(int x, int y)
{
    std::pair<int, int> pair;

    pair.first = x;
    pair.second = y;
    _mapSize = pair;
}

void GameState::setTeamName(std::vector<std::string> teams)
{
    for (std::size_t i = 1; i < teams.size(); i++) {
        if (teams[i] == "tna") {
            continue;
        }
        _teamsName.push_back(teams[i]);
    }
}

void GameState::setTile(std::vector<std::string> tile)
{
    Tile single_tile;

    single_tile.x = std::stoi(tile[1]);
    single_tile.y = std::stoi(tile[2]);
    single_tile.ressources.foodNb = std::stoi(tile[3]);
    single_tile.ressources.linemateNb = std::stoi(tile[4]);
    single_tile.ressources.deraumereNb = std::stoi(tile[5]);
    single_tile.ressources.siburNb = std::stoi(tile[6]);
    single_tile.ressources.mendianeNb = std::stoi(tile[7]);
    single_tile.ressources.phirasNb = std::stoi(tile[8]);
    single_tile.ressources.thystameNb = std::stoi(tile[9]);
    _tiles.push_back(single_tile);
}

void GameState::setAllTiles(std::vector<std::string> tiles)
{
    Tile single_tile;

    for (std::size_t i = 1; i < tiles.size(); i += 9) {
        single_tile.x = std::stoi(tiles[1]);
        single_tile.y = std::stoi(tiles[2]);
        single_tile.ressources.foodNb = std::stoi(tiles[3]);
        single_tile.ressources.linemateNb = std::stoi(tiles[4]);
        single_tile.ressources.deraumereNb = std::stoi(tiles[5]);
        single_tile.ressources.siburNb = std::stoi(tiles[6]);
        single_tile.ressources.mendianeNb = std::stoi(tiles[7]);
        single_tile.ressources.phirasNb = std::stoi(tiles[8]);
        single_tile.ressources.thystameNb = std::stoi(tiles[9]);
        _tiles.push_back(single_tile);
    }
}

void GameState::addPlayer(std::vector<std::string> player, std::vector<std::unique_ptr<Team>> &teams, std::unique_ptr<Sound> &sound)
{
    PlayerState p;
    p.id = std::stoi(player[1]);
    p.inventory.foodNb = 0;
    p.inventory.deraumereNb = 0;
    p.inventory.linemateNb = 0;
    p.inventory.mendianeNb = 0;
    p.inventory.phirasNb = 0;
    p.inventory.siburNb = 0;
    p.inventory.thystameNb = 0;
    p.is_egg = false;
    p.is_incantation_active = false;
    p.level = std::stoi(player[5]);
    p.old_x = std::stoi(player[2]);
    p.x = std::stoi(player[2]);
    p.old_y = std::stoi(player[3]);
    p.y = std::stoi(player[3]);
    p.orientation = std::stoi(player[4]);
    p.teamName = player[6];
    _players.push_back(p);
    sf::Vector2f startPosition(static_cast<float>(_mapSize.first * 128), static_cast<float>(_mapSize.second * 128));
    teams.push_back(std::make_unique<Team>(p.id, "gui_client/asset/pictures/character/walk.png", startPosition, 200.0f, 8.0f, sound));
}

void GameState::removePlayer(std::vector<std::string> player, std::vector<std::unique_ptr<Team>> &teams)
{
    std::size_t i = 0;

    for (; i < _players.size(); i++) {
        if (_players[i].id == std::stoi(player[1])) {
            break;
        }
    }
    for (std::size_t x = i; x < _players.size() - 1; x++) {
        std::swap(_players[i], _players[i + 1]);
    }
    _players.pop_back();
    i = 0;
    for (; i < teams.size(); i++) {
        if (teams[i]->getIndex() == std::stoi(player[1])) {
            teams[i].reset();
            break;
        }
    }
    for (std::size_t x = i; x < teams.size() - 1; x++) {
        std::swap(teams[i], teams[i + 1]);
    }
    teams.pop_back();
    teams.pop_back();
}

void GameState::startIncantation(std::vector<std::string> incantation)
{
    for (std::size_t i = 4; i < incantation.size(); i++) {
        for (auto p : _players) {
            if (p.id == std::stoi(incantation[i])) {
                p.is_incantation_active = true;
            }
        }
    }
}
void GameState::endIncantation(std::vector<std::string> incantation)
{
    int x = std::stoi(incantation[1]);
    int y = std::stoi(incantation[2]);
    int r = std::stoi(incantation[3]);

    for (auto &p : _players) {
        if (p.x == x && p.y == y) {
            p.is_incantation_active = false;
            if (r == 1) {
                p.level++;
            }
        }
    }
}

void GameState::updatePlayerPosition(std::vector<std::string> player, std::vector<std::unique_ptr<Team>> &teams)
{
    for (auto &p : _players) {
        if (p.id == std::stoi(player[1])) {
            p.old_x = p.x;
            p.old_y = p.y;
            p.x = std::stoi(player[2]);
            p.y = std::stoi(player[3]);
            p.orientation = std::stoi(player[4]);
            break;
        }
    }
    for (std::size_t i = 0; i < teams.size(); i++) {
        if (teams[i]->getIndex() == std::stoi(player[1])) {
            teams[i]->updatePosition(_players);
            break;
        }
    }
}

void GameState::updateTile(std::vector<std::string> tile)
{
    for (auto &t : _tiles) {
        if (t.x == std::stoi(tile[1]) && t.y == std::stoi(tile[2])) {
            t.ressources.foodNb = std::stoi(tile[3]);
            t.ressources.linemateNb = std::stoi(tile[4]);
            t.ressources.deraumereNb = std::stoi(tile[5]);
            t.ressources.siburNb = std::stoi(tile[6]);
            t.ressources.mendianeNb = std::stoi(tile[7]);
            t.ressources.phirasNb = std::stoi(tile[8]);
            t.ressources.thystameNb = std::stoi(tile[9]);
            break;
        }
    }
}

void GameState::updatePlayerInventory(std::vector<std::string> inventory)
{
    for (auto &p : _players) {
        if (p.id == std::stoi(inventory[1])) {
            p.old_x = p.x;
            p.old_y = p.y;
            p.x = std::stoi(inventory[2]);
            p.y = std::stoi(inventory[3]);
            p.inventory.foodNb = std::stoi(inventory[4]);
            p.inventory.linemateNb = std::stoi(inventory[5]);
            p.inventory.deraumereNb = std::stoi(inventory[6]);
            p.inventory.siburNb = std::stoi(inventory[7]);
            p.inventory.mendianeNb = std::stoi(inventory[8]);
            p.inventory.phirasNb = std::stoi(inventory[9]);
            p.inventory.thystameNb = std::stoi(inventory[10]);
            break;
        }
    }
}
