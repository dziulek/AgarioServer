#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "constants.hpp"
#include "glm/glm.hpp"

namespace agario{

    namespace shapes{

    class Circle : public Shape {

    public:

        Circle(){
            radius = MIN_RADIUS;
            area = PI * radius * radius;
            resultantForce = {0, 0};
        }
        Circle(float r) : radius(r){}

        void setRadius(float newR);
        float getRadius(){ return radius;}
        float static inline getDistance(const Circle & a, const Circle & b);
        static std::pair<glm::vec2, glm::vec2> retForcesBetweenTwoShapes(const Circle & s1, const Circle & s2);
    
    private:

        float radius;

    };

    } 
}



#endif