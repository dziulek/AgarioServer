#ifndef MAP_CONTROLLER_HPP
#define MAP_CONTROLLER_HPP

#include "../shapes/shape.hpp"
#include "map.hpp"

namespace agario{

using namespace shapes;

class MapController{

private:

    Map * map;

public:

    virtual void update() = 0;
    Map * getMap();

};

}



#endif