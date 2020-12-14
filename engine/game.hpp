#ifndef GAME_HPP
#define GAME_HPP

#include "./maps/map.hpp"
#include "player.hpp"
#include <vector>

namespace agario{

class Game{

private:

    Map * map;
    std::vector<Player *> players;
    int nOfPlayers = 0;

public:

    Map * getMap(){ return map;}
    void addPlayer()
};

}

#endif