#ifndef MAP_PLAYER_MOVEMENT_HPP
#define MAP_PLAYER_MOVEMENT_HPP

#include "shapes/shape.hpp"
#include "mapController.hpp"

#include <cmath>

#include <iostream>

namespace agario{

using namespace shapes;

class MapPlayerMovement : public MapController{

private:

    void check_borders();

public:

    MapPlayerMovement(Map * map) : MapController(map){

    }
    void update() override;
};

}

#endif