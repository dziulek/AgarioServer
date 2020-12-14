#ifndef MAP_BOMB_CONTROLLER_HPP
#define MAP_BOMB_CONTROLLER_HPP

#include "mapController.hpp"

namespace agario{

using namespace shapes;

class MapBombController : public MapController{

public:

    void update() override;

};

}


#endif