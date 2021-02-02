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

MoveableCircle & PlayerObject::operator[](int t){

    return *blobs[t].get();
}

void PlayerObject::setVelocities(){

    for(auto & b : blobs){

        glm::vec2 v = glm::normalize(mousePosition - b.get()->getPosition() + glm::vec2(0.25, 0.25));

        v *= b.get()->calculateVelocityMod();

        b.get()->setVelocity(v);
    }
}

void PlayerObject::addMass(const float mass, int mcIndex){

    blobs[mcIndex].get()->addMass(mass);
}

void PlayerObject::deleteIthElement(int i){

    blobs[i].reset();
    blobs[i] = std::move(blobs.back());

    blobs.pop_back();
}

std::pair<glm::vec2, glm::vec2> PlayerObject::getMinRectangle(){

    glm::vec2 left_upper = glm::vec2(PLUS_INFINITY, PLUS_INFINITY);
    glm::vec2 down_right = glm::vec2(MINUS_INFINITY, MINUS_INFINITY);

    for(auto & blob : blobs){

        left_upper.x = std::min(left_upper.x, blob.get()->getPosition().x - blob.get()->getRadius());
        left_upper.y = std::min(left_upper.y, blob.get()->getPosition().y - blob.get()->getRadius());

        down_right.x = std::max(down_right.x, blob.get()->getPosition().x + blob.get()->getRadius());
        down_right.y = std::max(down_right.y, blob.get()->getPosition().y + blob.get()->getRadius());
    }

    return {left_upper, down_right};
}

}