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

void WObject::move1(const float dTime){

    glm::vec2 old = this->velocity;

    float dirx, diry;

    this->velocity += this->acceleration * dTime;

    dirx = old.x * this->velocity.x;
    diry = old.y * this->velocity.y;

    if(glm::length(this->velocity) > eps || dirx > 0 || diry > 0)
        centerPosition += dTime * velocity;

    std::cout <<"a";
}
}//shapes

}//agario