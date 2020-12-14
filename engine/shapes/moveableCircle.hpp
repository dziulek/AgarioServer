#ifndef MOVABLE_CIRCLE_HPP
#define MOVABLE_CIRCLE_HPP

#include "circle.hpp"
#include "glm/glm.hpp"
#include <utility>
#include <cmath>

namespace agario{

namespace shapes{

class MoveableCircle : public Circle{

private:

    glm::vec2 velocity;
    void calculateVelocity();
    inline float calculateVelocityMod() const;

public:

    MoveableCircle(){
        Circle();
    }
    MoveableCircle(const glm::vec2 pos, const float radius) : Circle(radius, pos){}

    const glm::vec2 getVelocity() const;
    void setVelocity(const glm::vec2 v);
    void move(const float dTime);
    static std::pair<glm::vec2, glm::vec2> calculateGravityVelocities(const MoveableCircle & c1, const MoveableCircle & c2);

};

}//namespace shapes

}//namespace agario



#endif