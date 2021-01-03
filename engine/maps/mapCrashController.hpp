#ifndef MAP_CRASH_CONTROLLER_HPP
#define MAP_CRASH_CONTROLLER_HPP

#include "map.hpp"
#include "../shapes/allshapes.hpp"
#include <string>
#include <memory>

namespace agario{

using namespace shapes;

class MapCrashController : public MapController{

private:

    void crashCalculate(std::unique_ptr<MoveableCircle> & b1, std::unique_ptr<MoveableCircle> & b2);

public:

    MapCrashController(Map * map) : MapController(map){}

    void update() override;

};

}

#endif