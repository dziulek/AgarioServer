#ifndef GAME_HPP
#define GAME_HPP

#include "maps/map.hpp"
#include "maps/mapMiniController.hpp"
#include "maps/mapPlayerMovement.hpp"
#include "maps/mapCrashController.hpp"
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
        std::unique_ptr<MapController> miniController = std::make_unique<MapMiniController>(this->getMap());
        this->map->addController(miniController);
        std::unique_ptr<MapController> playerMovement = std::make_unique<MapPlayerMovement>(this->getMap());
        this->map->addController(playerMovement);
        std::unique_ptr<MapController> crashController = std::make_unique<MapCrashController>(this->getMap());
        this->map->addController(crashController);
    }
    ~Game(){

        delete map;
    }
    Map * getMap(){ return map;}
    int getnOfPlayers(){ return players.size();}
    Player & getPlayer(int index){ return *players[index].get();}
    Player & getPlayer(std::string ipaddr);

    Player * addPlayer(std::string nickaname = "");
    void deletePlayer(Player * player);
    glm::vec2 & getPlayerMousePosition(Player * p){ p->mousePosition;}
    void setPlayerMousePosition(Player * p, glm::vec2 pos){p->mousePosition = pos;}
    void mainLoop(const float dTime);

    void cullDeadPlayers();
};

}

#endif