#ifndef MOVABLE_CIRCLE_HPP
#define MOVABLE_CIRCLE_HPP

#include "circle.hpp"
#include "../glm/glm.hpp"
#include <utility>
#include <cmath>

namespace agario{

namespace shapes{

class MoveableCircle : public Circle{

private:

    glm::vec2 velocity;
    void calculateVelocity();
    

public:

    MoveableCircle(){
        Circle();
    }
    MoveableCircle(glm::vec2 pos, const float radius) : Circle(radius, pos){}
    virtual ~MoveableCircle(){}
    
    inline float calculateVelocityMod() const{
        return 40.4 * pow(this->getArea(), -0.439);
    };
    void addMass(const float mass);
    const glm::vec2 getVelocity() const;
    void setVelocity(const glm::vec2 v);
    void move(const float dTime);
    static std::pair<glm::vec2, glm::vec2> calculateGravityVelocities(const MoveableCircle & c1, const MoveableCircle & c2);

};

}//namespace shapes

}//namespace agario



#endif