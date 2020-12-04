#include "shape.hpp"

const float shapes::Shape::getArea() const{
    
    return this->area;
}

const glm::vec2 shapes::Shape::getPosition() const{

    return this->position;
}

void shapes::Shape::setPosition(const glm::vec2 newPos){

    this->position = newPos;
}

void shapes::Shape::move(const glm::vec2 vec){

    this->position = glm::vec2(position.x + vec.x, position.y + vec.y);
}

void shapes::Shape::setResultantForce(const glm::vec2 vec){

    this->resultantForce = vec;
}
