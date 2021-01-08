#include "map.hpp"

namespace agario{

using namespace shapes;

void Map::addPlayerObject(PlayerObject * po){

    this->playerObjects.push_back(po);
}

void Map::addController(MapController * controller){

    this->controllers.push_back(controller);
}

void Map::removeController(MapController * controller){

    
}

void Map::notify(){
    
    for(auto & c : controllers){

        c->update();
    }
}

}