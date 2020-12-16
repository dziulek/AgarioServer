#include "mapMiniController.hpp"

namespace agario{

using namespace shapes;

void MapMiniController::update(){

    cullDeadMinis();

    int missing = MAX_MINIS_ON_MAP - this->getMap()->minis.size();

    if(missing > MAX_MISSING_MINIS){

        int xFields = this->getMap()->minis[0].size();
        int yFields = this->getMap()->minis.size();

        for(int i = 0; i < missing; i++){

            //pick random map coordinates
            float x = distribution("uniform") * this->getMap()->width;
            float y = distribution("uniform") * this->getMap()->height;
            //[optional] check for collision with another mini

            //add to the map
            std::unique_ptr<Mini> valuePtr(new Mini({x, y}));
            this->getMap()->minis[int(y)][int(x)].push_back(std::move(valuePtr));
        }
    }

}

void MapMiniController::initMap(){

    //resize minis vector if needed

    //fill the map with minis

    for(int i = 0; i < MAX_MINIS_ON_MAP; i++){
        //pick random map roordinates
        float x = distribution("uniform") * this->getMap()->width;
        float y = distribution("uniform") * this->getMap()->height;
        //check for collision with another mini

        //add to the map
        Mini m = new Mini({x, y});
        this->getMap()->minis[int(y)][int(x)].push_back(m);
    }
}

void MapMiniController::cullDeadMinis(){

}

float MapMiniController::distribution(const std::string name){

    if(name == "uniform"){

        return static_cast<float>(rand()/RAND_MAX);
    }
    else if("gaussian"){
        
        return 1;
    }
     
    return -1;
}

}