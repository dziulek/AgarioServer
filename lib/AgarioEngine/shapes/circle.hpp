#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "../constants.hpp"
#include "../glm/glm.hpp"

namespace agario{

namespace shapes{

class Circle : public Shape {

protected:

    float radius;
    glm::vec2 centerPosition;
    unsigned int color = WHITE;

public:

    Circle(){
        radius = MIN_PLAYER_RADIUS;
        area = PI * radius * radius;
    }
    Circle(float r, glm::vec2 pos) : radius(r), centerPosition(pos){

        area = PI * radius * radius;
    }
    virtual ~Circle(){}

    glm::vec2 getPosition() const override;
    void calculateArea() override;
    static float getRadiusFromArea(const float area);
    void setRadius(const float newR);
    const float getRadius() const;
    uint32_t getColor() const { return this->color;}
    
    float static inline getDistance(const Circle & a, const Circle & b);

};

} 
}



#endif