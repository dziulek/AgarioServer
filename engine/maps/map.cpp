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

glm::vec2 Map::findPositionForNewPlayer(){

    bool occupied = true;

    float xPos, yPos;

    while(occupied){

        xPos = static_cast<float>(rand()) / RAND_MAX * width;
        yPos = static_cast<float>(rand()) / RAND_MAX * height;

        // for(auto & playerobject : playerObjects){

        //     float distance = glm::vec2(xPos, yPos) - playerobject 
        // }
        
        occupied = false;
    }

    return {xPos, yPos};
}

}