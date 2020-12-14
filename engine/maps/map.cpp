#include "map.hpp"

namespace agario{

using namespace shapes;

void Map::addPlayerObject(PlayerObject * po){

    PlayerObject * copy = po;
    playerObjects.push_back(copy);
}

void Map::addController(MapController * controller){

    this->controllers.push_back(controller);
}

void Map::removeController(MapController * controller){

    controller = nullptr;
}

}