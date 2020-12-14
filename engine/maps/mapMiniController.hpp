#ifndef MAP_MINI_CONTROLLER_HPP
#define MAP_MINI_CONTROLLER_HPP

#include "mapController.hpp"
#include "map.hpp"

namespace agario{

using namespace shapes;

class MapMiniController : public MapController{

public:

    void update() override;
};

}



#endif