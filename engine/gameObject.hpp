#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "./shapes/circle.hpp"
#include "constants.hpp"
#include "glm/glm.hpp"
#include <vector>

namespace agario{

using namespace shapes;

class GameObject {

public:

    virtual void setPosition(const glm::vec2 newPos) = 0;
    virtual void move(const glm::vec2 v) = 0;
    virtual void addMass(const float mass) = 0;
    virtual void divideObject() = 0;
};

}


#endif