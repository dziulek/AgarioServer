#include "circle.hpp"

namespace agario{
    
namespace shapes{

void Circle::setRadius(const float newR){

    if(newR < 0) this->radius = 0.0f;
    else this->radius = newR;
}

float Circle::getDistance(const Circle & a, const Circle & b){

    return glm::length(a.position - b.position);
}

std::pair<glm::vec2, glm::vec2> Circle::retForcesBetweenTwoShapes(const Circle & s1, const Circle & s2){

    float r = glm::length(s1.position - s2.position);
    float m1 = s1.area;
    float m2 = s2.area;

    if(r < s1.radius + s2.radius - eps){
        //circles must be separated
        //first method do nothing, they will separate automatically
        return {s1.getResultantForce(), s2.getResultantForce()};
    }

    //gravity forces
    glm::vec2 f1 = GRAVITY_CONST * s1.getArea() / (s2.position - s1.position) * (s2.position - s1.position);
    glm::vec2 f2 = GRAVITY_CONST * s2.getArea() / (s1.position - s2.position) * (s1.position - s2.position);

    return {f1, f2};
}

}

}



