/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** GameLoop
*/

#include <sstream>

#include "game/GameLoop.hpp"

GameLoop::GameLoop(const std::string &host, const std::string &port)
{
    std::string str;
    std::string copy;
    std::vector<std::string> vec;
    int x = 0;
    int y = 0;

    _gameState = std::make_unique<GameState>();
    try {
        _networkManager = std::make_unique<NetworkManager>(host, port);
        while (str != "WELCOME\n") {
            str = _networkManager->receive(1);
        }
        std::cout << str;
        str.clear();
        _networkManager->send("GRAPHIC", 1);
        while (str.empty()) {
            _networkManager->send("msz", 1);
            str = _networkManager->receive(1);
        }
        std::cout << str;
        vec = _parseMessage(str);
        str.clear();
        _gameState->setMapSize(std::stoi(vec[1]), std::stoi(vec[2]));
        vec.clear();
        while (str.empty()) {
            _networkManager->send("tna", 1);
            str = _networkManager->receive(1);
        }
        vec = _parseMessage(str);
        _gameState->setTeamName(vec);
        str.clear();
        vec.clear();
        for (int i = 0; i < _gameState->getMapSize().first * _gameState->getMapSize().second; i++) {
            std::string msg("bct ");
            msg.append(std::to_string(x) + " ");
            msg.append(std::to_string(y));
            while(str.empty()) {
                _networkManager->send(msg, 1);
                str = _networkManager->receive(1);
            }
            vec = _parseMessage(str);
            std::cout << str;
            _gameState->setTile(vec, true);
            x++;
            if (x == _gameState->getMapSize().first) {
                x = 0;
                y++;
            }
            str.clear();
            vec.clear();
        }
    } catch (const std::runtime_error &e) {
        throw std::runtime_error(e.what());
    }
}

GameLoop::~GameLoop()
{
    _gameState.reset();
    _networkManager.reset();
}

void GameLoop::runGame()
{
    std::string msg;
    std::vector<std::string> vec;

    while (true) {
        msg = _networkManager->receive(1);
        if (!msg.empty()) {
            vec = _parseMessage(msg);
            _whichMessage(vec);
        } else {
            _retrieveInformations();
        }
        msg.clear();
        vec.clear();
        // Put sfml here
    }
}

std::vector<std::string> GameLoop::_parseMessage(const std::string &msg)
{
    std::istringstream iss(msg);
    std::vector<std::string> to_vector;
    std::string word;

    while (iss >> word) {
        to_vector.push_back(word);
    }
    return to_vector;
}

void GameLoop::_whichMessage(const std::vector<std::string> vec)
{
    std::string msg;
    std::string sendMsg;
    std::vector<std::string> parsed_msg;

    if (vec[0] == "pnw") { // New player connected
        _gameState->addPlayer(vec);
    }
    if (vec[0] == "pic") { // Incantation start
        _gameState->startIncantation(vec);
    }
    if (vec[0] == "pie") { // Incantation end
        _gameState->endIncantation(vec);
    }
    if (vec[0] == "pdi") { // Player death
        _gameState->removePlayer(vec);
    }
    if (vec[0] == "pdr" || vec[0] == "pgt") { // Ressource dropping and collecting
        try {
            sendMsg.assign("bct ");
            sendMsg.append(std::to_string(_gameState->getSinglePlayer(std::stoi(vec[1])).x) + " ");
            sendMsg.append(std::to_string(_gameState->getSinglePlayer(std::stoi(vec[1])).y));
            while (msg.empty()) {
                _networkManager->send(sendMsg, 1);
                msg = _networkManager->receive(1);
            }
            parsed_msg = _parseMessage(msg);
            _gameState->updateTile(parsed_msg);
            sendMsg.clear();
            msg.clear();
            parsed_msg.clear();
            sendMsg.assign("pin ");
            sendMsg.append(vec[1]);
            while (msg.empty()) {
                _networkManager->send(sendMsg, 1);
                msg = _networkManager->receive(1);
            }
            parsed_msg = _parseMessage(msg);
            _gameState->updatePlayerInventory(parsed_msg);
        } catch (const std::runtime_error &e) {
            std::cerr(e.what());
        }
    }
}

void GameLoop::_retrieveInformations()
{
    std::string msg;
    std::string sendMsg;
    std::vector<std::string> parsed_msg;

    for (int i = 0; i < _gameState->getPlayers().size(); i++) {
        sendMsg.assign("ppo ");
        sendMsg.append(std::to_string(_gameState->getPlayers()[i].id));
        while (msg.empty()) {
            _networkManager->send(sendMsg, 1);
            msg = _networkManager->receive(1);
        }
        parsed_msg = _parseMessage(msg);
        _gameState->updatePlayerPosition(parsed_msg);
        sendMsg.clear();
        msg.clear();
        parsed_msg.clear();
    }
}
