#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace shapes{

class Circle : Shape {

public:

    Circle();
    Circle(const unsigned int r,const glm::vec2 center) : radius(r){
        
        this->position = center;
    }

    void setRadius(const float newR);
    float static inline getDistance(const Circle & a, const Circle & b);

private:

    float radius;

};

}

#endif