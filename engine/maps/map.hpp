#ifndef MAP_HPP
#define MAP_HPP

#include "engine/shapes/shape.hpp"
#include "engine/allshapes.hpp"
#include "engine/playerObject.hpp"
#include "engine/bomb.hpp"
#include "engine/maps/mapController.hpp"
#include <vector>
#include <memory>

namespace agario{

using namespace shapes;

class Map{

private:

    float width;
    float height;

    std::vector<std::vector<std::vector<std::unique_ptr<const Mini *>>>> minis;
    std::vector<std::unique_ptr<Bomb *>> bombs;
    std::vector<std::unique_ptr<PlayerObject *>> playerObjects;

    std::vector<std::unique_ptr<MapController *>> controllers;

public:
    

    void addPlayerObject(PlayerObject * po);
    void addController(MapController * controller);
    void removeController(MapController * controller);
    

    friend class MapMiniController;
    friend class MapBombController;
};

}


#endif