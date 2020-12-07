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

std::pair<glm::vec2, glm::vec2> Circle::retForcesBetweenTwoShapes(const Circle & s1, const Circle & s2);
    
    float r = glm::length(s1.position - s2.position);
    float m1 = s1.area;
    float m2 = s2.area;

    if(r < s1.radius + s2.radius){
        //circles must be separated

    }
    else {
        //gravity forces
    }

    }

}



