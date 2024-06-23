/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** GameLoop
*/

#include <sstream>

#include <SFML/Graphics.hpp>
#include "game/GameLoop.hpp"

GameLoop::GameLoop(const std::string &host, const std::string &port)
: followPlayer(false)
{
    std::string str;
    std::string copy;
    std::vector<std::string> vec;

    _gameState = std::make_unique<GameState>();
    try {
        _networkManager = std::make_unique<NetworkManager>(host, port);
        while (str != "WELCOME\n") {
            str = _networkManager->receive(1);
        }
        str.clear();
        _networkManager->send("GRAPHIC", 1);
        while (str.empty()) {
            _networkManager->send("msz", 1);
            str = _networkManager->receive(1);
        }
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
        while (str.empty()) {
            _networkManager->send("mct", 10);
            str = _networkManager->receive(1);
        }
        vec = _parseMessage(str);
        _gameState->setAllTiles(vec);
        str.clear();
        vec.clear();
    } catch (const std::runtime_error &e) {
        throw std::runtime_error(e.what());
    }
    graphic = std::make_unique<Graphic>();
    graphic->initWindow(1920, 1080, "My Zappy");
    resource = std::make_unique<Resource>("gui_client/asset/pictures/resources/flower_grass.png");
    resource->addMaterial("food", "gui_client/asset/pictures/resources/food.png");
    resource->addMaterial("linemate", "gui_client/asset/pictures/resources/linemate.png");
    resource->addMaterial("deraumere", "gui_client/asset/pictures/resources/deraumere.png");
    resource->addMaterial("sibur", "gui_client/asset/pictures/resources/sibur.png");
    resource->addMaterial("mendiane", "gui_client/asset/pictures/resources/mendiane.png");
    resource->addMaterial("phiras", "gui_client/asset/pictures/resources/phiras.png");
    resource->addMaterial("thystame", "gui_client/asset/pictures/resources/thystame.png");
    sound = std::make_unique<Sound>();
    sound->loadMusic("gui_client/asset/sound/C418 - Moog City.ogg");
    sound->loadSound("footsteps", "gui_client/asset/sound/footstep.ogg");
    volumeVisualizer = std::make_unique<VolumeVisualizer>(200.0f, 20.0f);
    volumeVisualizer->setVolume(sound->getMusicVolume());
    resource->generateMap(_gameState->getMapSize().first, _gameState->getMapSize().second);
    resource->generateMaterials();
    graphic->setMapSize(resource->getMapWidth(), resource->getMapHeight());
}

GameLoop::~GameLoop()
{
    _gameState.reset();
    _networkManager.reset();
    sound.reset();
    volumeVisualizer.reset();
    resource.reset();
    graphic.reset();
}

void GameLoop::runGame()
{
    std::string msg;
    std::vector<std::string> vec;
    sf::RenderWindow &window = graphic->getWindow();

    sound->playMusic();
    while (window.isOpen() == true) {
        if (event.type == sf::Event::Closed) {
            window.close();
            continue;
        }
        msg = _networkManager->receive(30);
        if (!msg.empty()) {
            vec = _parseMessage(msg);
            _whichMessage(vec);
        } else {
            _retrieveInformations();
        }
        msg.clear();
        vec.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            volumeVisualizer->manageVolume(sound);
        }
        sf::Time elapsed = clock.restart();
        graphic->updateView(elapsed.asSeconds());
        // resource.checkCollision(team.getPosition());
        window.clear();
        resource->draw(window);
        for (std::size_t i = 0; i < teams.size(); i++) {
            teams[i]->updateTime(elapsed);
            teams[i]->draw(window);
        }
        window.display();
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
        _gameState->addPlayer(vec, teams, sound);
    }
    if (vec[0] == "pic") { // Incantation start
        _gameState->startIncantation(vec);
    }
    if (vec[0] == "pie") { // Incantation end
        _gameState->endIncantation(vec);
    }
    if (vec[0] == "pdi") { // Player death
        _gameState->removePlayer(vec, teams);
    }
    if (vec[0] == "pdr" || vec[0] == "pgt") { // Ressource dropping and collecting
        try {
            sendMsg.assign("bct ");
            sendMsg.append(std::to_string(_gameState->getSinglePlayer(std::stoi(vec[1])).x) + " ");
            sendMsg.append(std::to_string(_gameState->getSinglePlayer(std::stoi(vec[1])).y));
            while (msg.empty()) {
                _networkManager->send(sendMsg, 10);
                msg = _networkManager->receive(10);
            }
            parsed_msg = _parseMessage(msg);
            _gameState->updateTile(parsed_msg);
            sendMsg.clear();
            msg.clear();
            parsed_msg.clear();
            sendMsg.assign("pin ");
            sendMsg.append(vec[1]);
            while (msg.empty()) {
                _networkManager->send(sendMsg, 10);
                msg = _networkManager->receive(10);
            }
            parsed_msg = _parseMessage(msg);
            _gameState->updatePlayerInventory(parsed_msg);
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void GameLoop::_retrieveInformations()
{
    std::string msg;
    std::string sendMsg;
    std::vector<std::string> parsed_msg;

    if (_gameState->getPlayers().size() == 0) {
        return;
    }
    for (std::size_t i = 0; i < _gameState->getPlayers().size(); i++) {
        sendMsg.assign("ppo ");
        sendMsg.append(std::to_string(_gameState->getPlayers()[i].id));
        while (msg.empty()) {
            _networkManager->send(sendMsg, 10);
            msg = _networkManager->receive(10);
        }
        parsed_msg = _parseMessage(msg);
        if (parsed_msg[0] == "sbp") {
            continue;
        }
        _gameState->updatePlayerPosition(parsed_msg, teams);
        sendMsg.clear();
        msg.clear();
        parsed_msg.clear();
    }
}
