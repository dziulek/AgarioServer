#ifndef MAP_HPP
#define MAP_HPP

#include "../allshapes.hpp"
#include "../playerObject.hpp"
#include "../bomb.hpp"
#include "mapController.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <cmath>
#include <stdlib.h>

namespace agario{

using namespace shapes;

class PlayerObject;
class MapController;

class Map{

private:

    std::vector<std::unique_ptr<MapController>> controllers;

public:

    std::vector<std::vector<std::vector<std::unique_ptr<const Mini>>>> minis;
    std::vector<std::unique_ptr<Bomb>> bombs;
    std::vector<PlayerObject *> playerObjects;

    int nOfMinis = 0;
    
    float width;
    float height;

    Map(){
        width = 100.0f;
        height = 100.0f;
    }

    ~Map(){

    }

    void addPlayerObject(PlayerObject * po);
    void addController(std::unique_ptr<MapController> & controller);
    void removeController(MapController * controller);

    glm::vec2 findPositionForNewPlayer();
    std::pair<std::pair<int, int>, std::pair<int, int>> getMiniRects(glm::vec2 lu, glm::vec2 rd);

    void notify();
    

    // friend class MapMiniController;
    // friend class MapBombController;
};

}
#endif
