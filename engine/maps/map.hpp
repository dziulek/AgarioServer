#ifndef MAP_HPP
#define MAP_HPP

#include "../shapes/allshapes.hpp"
#include "../playerObject.hpp"
#include "../bomb.hpp"
// #include "mapController.hpp"
#include <vector>
#include <memory>

namespace agario{

using namespace shapes;

class Map{

private:

    std::vector<std::vector<std::vector<std::unique_ptr<const Mini>>>> minis;
    std::vector<std::unique_ptr<Bomb>> bombs;
    std::vector<PlayerObject *> playerObjects;

    // std::vector<std::unique_ptr<MapController>> controllers;

public:
    
    float width;
    float height;

    Map(){
        width = 1000.0f;
        height = 600.0f;
    }

    void addPlayerObject(PlayerObject * po);
    // void addController(MapController & controller);
    // void removeController(MapController & controller);
    

    // friend class MapMiniController;
    // friend class MapBombController;
};

}


#endif