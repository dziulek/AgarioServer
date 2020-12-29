#include "playerObject.hpp"

namespace agario{

using namespace shapes;

void PlayerObject::divideObject(){

}

void PlayerObject::addMass(const float mass){

    
}

void PlayerObject::move(const float dTime){

    for(auto & mc : blobs){

        mc->move(dTime);
    }
}

void PlayerObject::setPosition(const glm::vec2 pos){

}

float PlayerObject::getTotalArea(){

    float sum = 0;

    for(auto & mc : blobs){
        sum += mc->getArea();
    }

    return sum;
}

int PlayerObject::getSize(){

    return this->blobs.size();
}

agario::shapes::MoveableCircle & PlayerObject::operator[](int t){

    return *blobs[t];
}

}