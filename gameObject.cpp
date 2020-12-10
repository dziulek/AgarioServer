#include "gameObject.hpp"

namespace agario{

using namespace shapes;

shapes::Circle & GameObject::operator[](unsigned int i){

    return *this->sparkles[i];
}

void GameObject::setPosition(const glm::vec2 newPos){

}

void GameObject::move(const glm::vec2 cursorPos, const float time){

    //calculates forces between all pairs, including cursor position
    setAlmostFinalResultantForces(cursorPos);
    //
    calculateFinalResultantForces(cursorPos);
    
    
    for(int i = 0; i < sparkles.size(); i++){
        //change coordinates
        sparkles[i]->setPosition(sparkles[i]->getPosition() + sparkles[i]->getResultantForce() * time);
    }
}

void GameObject::giveMass(const glm::vec2 direction){

    for(int i = 0; i < sparkles.size(); i ++){

    }
}

void GameObject::addMass(const float mass){

}

void GameObject::bombAction(){

}

void GameObject::divideObject(){
    

    compoundAvailable = false;
}

void GameObject::setAlmostFinalResultantForces(const glm::vec2 cursorPos){

    glm::vec2 out_f;

    for(int i = 0; i < sparkles.size(); i++){

        out_f = OUT_FORCE_VALUE * glm::normalize(cursorPos - sparkles[i]->getPosition);
        sparkles[i]->setResultantForce(out_f);

    }

}

void GameObject::calculateFinalResultantForces(){


}

}