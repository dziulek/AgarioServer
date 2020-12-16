#ifndef MAP_HPP
#define MAP_HPP

#include "../shapes/shape.hpp"
#include "../allshapes.hpp"
#include "../playerObject.hpp"
#include "../bomb.hpp"
#include "mapController.hpp"
#include <vector>

namespace agario{

using namespace shapes;

class Map{

private:

    float width;
    float height;

    std::vector<std::vector<std::vector<const Mini *>>> minis;
    std::vector<Bomb *> bombs;
    std::vector<PlayerObject *> playerObjects;

    std::vector<MapController *> controllers;

public:
    

    void addPlayerObject(PlayerObject * po);
    void addController(MapController * controller);
    void removeController(MapController * controller);
    

    friend class MapMiniController;
    friend class MapBombController;
};

}


#endif