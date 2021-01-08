#ifndef MAP_HPP
#define MAP_HPP

#include "../shapes/allshapes.hpp"
#include "../playerObject.hpp"
#include "../bomb.hpp"
#include "mapController.hpp"
#include <vector>
#include <memory>

namespace agario{

using namespace shapes;

class PlayerObject;
class MapController;

class Map{

private:

    std::vector<MapController *> controllers;

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

    void addPlayerObject(PlayerObject * po);
    void addController(MapController * controller);
    void removeController(MapController * controller);
    void notify();
    

    friend class MapMiniController;
    // friend class MapBombController;
};

}

// namespace agario{

// using namespace shapes;

// class MapController{

// protected:

//     Map * map;

// public:

//     MapController(Map * map){
//         this->map = map; 
//         this->map->addController(this);
//     }
//     virtual void update() = 0;
//     Map * getMap();

// };

// }
#endif
