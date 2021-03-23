#ifndef MOVABLE_CIRCLE_HPP
#define MOVABLE_CIRCLE_HPP

#include "circle.hpp"
#include "../glm/glm.hpp"
#include <utility>
#include <cmath>
#include <iostream>

namespace agario{

namespace shapes{

class MoveableCircle : public Circle{

protected:

    glm::vec2 acceleration = {0, 0};
    glm::vec2 velocity = {0,0};
    void calculateVelocity();
    // glm::vec2 calcResultantForce();
    

public:

    MoveableCircle(){
        Circle();
    }
    MoveableCircle(glm::vec2 pos, const float radius) : Circle(radius, pos){}
    virtual ~MoveableCircle(){}
    
    inline float calculateVelocityMod() const{
        return 40.4 * pow(this->getArea(), -0.239);
    };
    void addMass(const float mass);
    const glm::vec2 getVelocity() const;
    void setVelocity(const glm::vec2 v);
    void setColor(uint32_t color){ this->color = color;}
    virtual void move(const float dTime);
    static std::pair<glm::vec2, glm::vec2> calculateGravityVelocities(const MoveableCircle & c1, const MoveableCircle & c2);
    void setAcceleration(glm::vec2 acc){this->acceleration = acc;}
};

}//namespace shapes

}//namespace agario



#endif