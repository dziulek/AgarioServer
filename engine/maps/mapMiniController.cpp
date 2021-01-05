#include "mapMiniController.hpp"

namespace agario{

using namespace shapes;

void MapMiniController::update(){

    float fieldWidth = 50.0f;

    cullDeadMinis();

    int missing = MAX_MINIS_ON_MAP - this->getMap()->nOfMinis;

    if(missing > MAX_MISSING_MINIS){

        int xFields = this->getMap()->minis[0].size();
        int yFields = this->getMap()->minis.size();

        for(int i = 0; i < missing; i++){

            //pick random map coordinates
            float x = distribution("uniform") * this->getMap()->width;
            float y = distribution("uniform") * this->getMap()->height;
            //[optional] check for collision with another mini
            //not necessary
            //add to the map
            this->getMap()->minis[int(y / fieldWidth)][int(x / fieldWidth)].push_back(std::unique_ptr<Mini>(new Mini({x, y})));
            
        }
        this->map->nOfMinis+=missing;
    }

}

void MapMiniController::initMap(){

    float fieldWidth = 50.0f;
    //resize minis vector if needed
    this->map->minis.resize(int(map->height / fieldWidth) + 1);
    for(int i = 0; i < map->minis.size(); i++)
        map->minis[i].resize(int(map->width / fieldWidth) + 1);
    //fill the map with minis

    for(int i = 0; i < MAX_MINIS_ON_MAP; i++){
        //pick random map roordinates
        float x = distribution("uniform") * this->getMap()->width;
        float y = distribution("uniform") * this->getMap()->height;
        //check for collision with another mini
        //not necessary
        //add to the map
        this->getMap()->minis[int(y / fieldWidth)][int(x / fieldWidth)].push_back(std::unique_ptr<Mini>(new Mini({x, y})));
    }
    map->nOfMinis = MAX_MINIS_ON_MAP;
}

void MapMiniController::cullDeadMinis(){

    float fieldWidth = 50.0f;
    for(PlayerObject * p : map->playerObjects){

        for(int i = 0; i < p->getSize(); i++){

            //x coordinates
            int lowerBoundx = floor(((*p)[i].getPosition().x - (*p)[i].getRadius()) / fieldWidth); 
            int upperBoundx = ceil(((*p)[i].getPosition().x + (*p)[i].getRadius()) / fieldWidth);
            //y coordinates
            int lowerBoundy = floor(((*p)[i].getPosition().y - (*p)[i].getRadius()) / fieldWidth);
            int upperBoundy = ceil(((*p)[i].getPosition().y + (*p)[i].getRadius()) / fieldWidth);

            for(int j = lowerBoundx; j < upperBoundx; j++){
                
                for(int k = lowerBoundy; k < upperBoundy; k++){

                    for(auto & mc : map->minis[k][j]){
                        
                        if(mc.get() != nullptr && glm::length(mc->getPosition() - (*p)[i].getPosition()) < (*p)[i].getRadius()){
                            
                            float mass = mc.get()->getArea();
                            mc.reset();
                            mc = std::move(map->minis[k][j].back());
                            map->minis[k][j].pop_back();
                            map->nOfMinis--;

                            (*p)[i].addMass(mass);
                        }       
                    }
                }   
            }
        }
    }
}

float MapMiniController::distribution(const std::string name){

    if(name == "uniform"){

        return static_cast<float>(rand())/RAND_MAX;
    }
    else if(name == "gaussian"){
        
        return 1;
    }
     
    return -1;
}

}