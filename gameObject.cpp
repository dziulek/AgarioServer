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
    setAlmostFinalResultantForces();
    //
    calculateFinalResultantForces();
    
    
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
    
    glm::vec2 direction;
    const int s = sparkles.size();

    for(int i = 0; i < s; i++){

        Circle * c = new Circle(sparkles[i]->getRadius());

        direction = *cursorPosition - sparkles[i]->getPosition();
        c->setResultantForce(direction * DIVIDE_FORCE);

        sparkles.push_back(c);
    }
    compoundAvailable = false;
}

void GameObject::setAlmostFinalResultantForces(){

    glm::vec2 out_f;

    for(int i = 0; i < sparkles.size(); i++){

        out_f = OUT_FORCE_VALUE * glm::normalize(*cursorPosition - sparkles[i]->getPosition());
        sparkles[i]->setResultantForce(out_f);

    }

}

void GameObject::calculateFinalResultantForces(){


}

}