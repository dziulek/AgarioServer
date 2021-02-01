#include "map.hpp"

namespace agario{

using namespace shapes;

void Map::addPlayerObject(PlayerObject * po){

    this->playerObjects.push_back(po);
}

void Map::addController(std::unique_ptr<MapController> & controller){

    this->controllers.push_back(std::move(controller));
}

void Map::removeController(MapController * controller){

    
}

void Map::notify(){
    
    for(auto & c : controllers){

        c.get()->update();
    }
}

glm::vec2 Map::findPositionForNewPlayer(){

    bool occupied = true;

    float xPos, yPos;

    while(occupied){

        xPos = static_cast<float>(rand()) / RAND_MAX * width;
        yPos = static_cast<float>(rand()) / RAND_MAX * height;

        std::cout << xPos << " " << yPos << std::endl;

        // for(auto & playerobject : playerObjects){

        //     float distance = glm::vec2(xPos, yPos) - playerobject 
        // }
        
        occupied = false;
    }

    // return {xPos, yPos};
    return {100, 100};
}

std::pair<std::pair<int, int>, std::pair<int, int>> Map::getMiniRects(glm::vec2 left_up, glm::vec2 right_down){

    std::pair<int, int> lu, rd;

    lu.first = std::max((int)0, (int)(left_up.x / MINI_WIDTH));
    lu.second = std::max((int)0, (int)(left_up.y / MINI_WIDTH));

    rd.first = std::min((int)minis[0].size(), (int)ceil(right_down.x / MINI_WIDTH));
    rd.second = std::min((int)minis.size(), (int)ceil(right_down.y / MINI_WIDTH));

    return {lu, rd};
}

}