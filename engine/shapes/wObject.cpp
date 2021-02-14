#include "wObject.hpp"

namespace agario{

namespace shapes{

bool WObject::checkIfStop(){

    return glm::length(this->velocity) > eps ? false : true;
}

void WObject::stopObject(){

    this->velocity = {0.0, 0.0};
    this->isMove = false;
}

void WObject::slowDown(){


}

void WObject::move(const float dTime){

    if(isMove == true){
        this->time += dTime;

        glm::vec2 old = this->velocity;

        float dirx, diry;

        this->velocity += accelerationFunction() * dTime;

        // std::cout << glm::length(accelerationFunction()) << std::endl;

        dirx = old.x * this->velocity.x;
        diry = old.y * this->velocity.y;

        if(dirx < 0 || diry < 0){
            this->isMove = false;
        }


        centerPosition += this->velocity * dTime;        
    }


}

glm::vec2 WObject::accelerationFunction(){

    return this->acceleration * (float)(-pow(2, this->time * 3.9) + 20.0f);
    // return this->acceleration * (float)sin(this->time);
    
}
}//shapes

}//agario