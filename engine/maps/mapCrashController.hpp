#ifndef MAP_CRASH_CONTROLLER_HPP
#define MAP_CRASH_CONTROLLER_HPP

#include "map.hpp"
#include "../allshapes.hpp"
#include <string>
#include <memory>

namespace agario{

using namespace shapes;

class MapCrashController : public MapController{

private:

    bool crashCalculate(MoveableCircle & b1, MoveableCircle & b2);

public:

    MapCrashController(Map * map) : MapController(map){}

    void update() override;

};

}

#endif