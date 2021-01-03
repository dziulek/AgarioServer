#include "mapCrashController.hpp"

namespace agario{

using namespace shapes;

void MapCrashController::update(){

    //naive version, begin with the simplest algorithm
    for(PlayerObject * p1 : this->getMap()->playerObjects){

        for(PlayerObject * p2 : this->getMap()->playerObjects){

            for(int i1 = 0; i1 < p1->getSize(); i1++){

                for(int i2 = 0; i2 < p2->getSize(); i2++){

                    float distance = glm::length((*p1)[i1].getPosition() - (*p2)[i2].getPosition());
                    if(distance < std::max((*p1)[i1].getRadius(), (*p2)[i2].getRadius())){
                        //handle crash

                    }
                }
            }
        }
    }
}

void MapCrashController::crashCalculate(std::unique_ptr<MoveableCircle> & b1, std::unique_ptr<MoveableCircle> & b2){

    
}

}