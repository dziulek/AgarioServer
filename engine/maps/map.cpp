#include "map.hpp"

namespace agario{

using namespace shapes;

void Map::addPlayerObject(PlayerObject * po){

    this->playerObjects.push_back(po);
}

// void Map::addController(MapController & controller){

//     // this->controllers.emplace_back(std::make_unique<MapController>(controller));
//     int nothing;
// }

// void Map::removeController(MapController & controller){

//     int nothing;
// }

}