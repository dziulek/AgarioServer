#include "map.hpp"

namespace agario{

using namespace shapes;

void Map::addPlayerObject(PlayerObject * po){

    this->playerObjects.push_back(po);
}

void Map::addController(MapController * controller){

    controllers.push_back(controller);
}

void Map::removeController(MapController * controller){

    
}

}