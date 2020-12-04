#include "circle.hpp"

namespace shapes{

void Circle::setRadius(const float newR){

    if(newR < 0) this->radius = 0.0f;
    else this->radius = newR;
}

float Circle::getDistance(const Circle & a, const Circle & b){

    return glm::length(a.position - b.position);
}

}

