#ifndef MAP_MINI_CONTROLLER_HPP
#define MAP_MINI_CONTROLLER_HPP

// #include "mapController.hpp"
#include "map.hpp"
#include "../shapes/allshapes.hpp"
#include "mapController.hpp"
#include <string>
#include <memory>

namespace agario{

using namespace shapes;

class MapMiniController : public MapController{

private:

    void initMap();
    float distribution(const std::string name);
    void cullDeadMinis();

public:

    MapMiniController(Map * map) : MapController(map){

        initMap();
    }

    void update() override;
};

}



#endif