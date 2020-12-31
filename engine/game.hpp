#ifndef GAME_HPP
#define GAME_HPP

#include "maps/map.hpp"
#include "player.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <memory>

namespace agario{

class Game{

private:

    Map * map;
    std::vector<std::unique_ptr<Player>> players;
    int nOfPlayers = 0;

public:

    Game(){
        this->map = new Map;
    }
    ~Game(){
        delete map;
    }
    Map * getMap(){ return map;}
    int getnOfPlayers(){ return nOfPlayers;}
    Player & getPlayer(int index){ return *players[index].get();}
    Player & getPlayer(std::string ipaddr);
    void addPlayer();
    glm::vec2 & getPlayerMousePosition(Player * p){ p->mousePosition;}
    void setPlayerMousePosition(Player * p, glm::vec2 pos){p->mousePosition = pos;}
    void mainLoop(const float dTime);
};

}

#endif