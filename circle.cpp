#include "circle.hpp"

void shapes::Circle::setRadius(const float newR){

    if(newR < 0) this->radius = 0.0f;
    else this->radius = newR;
}