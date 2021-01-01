#include "circle.hpp"

namespace agario{
    
namespace shapes{

void Circle::setRadius(const float newR){

    if(newR < 0) this->radius = 0.0f;
    else this->radius = newR;
}

float Circle::getDistance(const Circle & a, const Circle & b){

    return glm::length(a.centerPosition - b.centerPosition);
}

const float Circle::getRadius() const{

    return this->radius;
} 

void Circle::calculateArea(){

    this->area = PI * radius * radius;
}

glm::vec2 Circle::getPosition() const{
    
    return this->centerPosition;
}

float Circle::getRadiusFromArea(){

    return sqrt(this->area / PI);
}

}

}



