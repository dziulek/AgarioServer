#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "constants.hpp"
#include "glm/glm.hpp"

namespace agario{

namespace shapes{

class Circle : public Shape {

protected:

    float radius;
    glm::vec2 centerPosition;

public:

    Circle(){
        radius = MIN_PLAYER_RADIUS;
        area = PI * radius * radius;
    }
    Circle(float r, const glm::vec2 pos) : radius(r), centerPosition(pos){

        area = PI * radius * radius;
    }

    const glm::vec2 getPosition() const override;
    void calculateArea() override;
    void setRadius(const float newR);
    const float getRadius() const;
    
    float static inline getDistance(const Circle & a, const Circle & b);

};

} 
}



#endif