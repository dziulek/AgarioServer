#ifndef MAP_BOMB_CONTROLLER_HPP
#define MAP_BOMB_CONTROLLER_HPP

#include "mapController.hpp"

namespace agario{

using namespace shapes;

class MapBombController : public MapController{

private:

    void initMap();

public:

    MapBombController(Map * map) : MapController(map){

        initMap();
    }

    void update() override;

};

}


#endif