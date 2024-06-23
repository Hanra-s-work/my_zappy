/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameState.hpp
*/

#ifndef GAMESTATE_HPP
    #define GAMESTATE_HPP

    #include <string>
    #include <vector>
    #include <istream>

struct Ressources {
    int foodNb;
    int linemateNb;
    int deraumereNb;
    int siburNb;
    int mendianeNb;
    int phirasNb;
    int thystameNb;
};

struct PlayerState {
    int id;
    int old_x;
    int old_y;
    int x;
    int y;
    int orientation;
    int level;
    std::string teamName;
    bool is_incantation_active;
    bool is_egg;
    Ressources inventory;
};

struct Tile {
    int x;
    int y;
    Ressources ressources;
};

class GameState {
    public:
        GameState();
        ~GameState();

        std::vector<PlayerState> getPlayers() const;
        std::vector<Tile> getTiles() const;
        std::pair<int, int> getMapSize() const;
        std::vector<std::string> getTeamsName() const;
        PlayerState getSinglePlayer(int id) const;
        Tile getSingleTile(int x, int y) const;

        void setMapSize(int x, int y);
        void setTeamName(std::vector<std::string> team);
        void setTile(std::vector<std::string> tile, bool is_init);

        void addPlayer(std::vector<std::string> player);
        void removePlayer(std::vector<std::string> player);
        void startIncantation(std::vector<std::string> incantation);
        void endIncantation(std::vector<std::string> incantation);
        void updatePlayerPosition(std::vector<std::string> player);
        void updateTile(std::vector<std::string> tile);
        void updatePlayerInventory(std::vector<std::string> inventory);

    private:
        std::vector<PlayerState> _players;
        std::vector<Tile> _tiles;
        std::vector<std::string> _teamsName;
        std::pair<int, int> _mapSize; // First = x, Second = y
};

#endif
