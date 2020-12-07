#include "gameObject.hpp"

namespace agario{

using namespace shapes;

void GameObject::setPosition(const glm::vec2 newPos){

}

void GameObject::move(const glm::vec2 cursorPos, const float time){
    //calculate forces between all pairs, including cursor position
    setAlmostResultantForces(cursorPos);
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

void GameObject::setAlmostResultantForces(){


}

void GameObject::calculateFinalResultantForces(){


}

}