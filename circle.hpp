#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace agario{

    namespace shapes{

    class Circle : public Shape {

    public:

        Circle();
        Circle(const unsigned int r,const glm::vec2 center) : radius(r){
            
            this->position = center;
        }

        void setRadius(const float newR);
        float getRadius(){ return radius;}
        float static inline getDistance(const Circle & a, const Circle & b);
        static std::pair<glm::vec2, glm::vec2> retForcesBetweenTwoShapes(const Circle & s1, const Circle & s2);
    
    private:

        float radius;

    };

    } 
}



#endif