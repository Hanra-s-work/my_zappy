/*
** EPITECH PROJECT, 2024
** new
** File description:
** GameState.hpp
*/

#ifndef GAMESTATE_HPP
    #define GAMESTATE_HPP

    #include <vector>
    #include <istream>
    #include <unordered_map>

struct PlayerState {
    int id;
    int x;
    int y;
    int orientation;
    int level;
    std::string teamName;
};

struct Tile {
    int x, y;
    int resources[7];
};

class GameState
{
    public:
        std::string getMsz() const;
        std::string getBct(int x, int y);
        std::string getMct() const;
        std::string getTna();
        std::vector<std::string> getPpo();
        std::vector<std::string> getPnw();


        void addPlayer(const PlayerState& player);
        std::vector<PlayerState> getPlayers() const;

        void updatePlayerPosition(int id, int x, int y, int orientation);

    private:
        std::string _msz;
        std::vector<std::string> _bct;
        std::string _mct;
        std::string _tna;
        std::vector<std::string> _ppo;
        std::vector<std::string> _pnw;
        // std::mutex _mtx;
        std::vector<PlayerState> players;
        std::unordered_map<int, Tile> tiles;
};

#endif
