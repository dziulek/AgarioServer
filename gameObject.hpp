#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <gml.hpp>

namespace game{

class GameObject {

    virtual void setPosition(const glm::vec2 newPos);
    virtual void move(const glm::vec2 vec);
    virtual void giveMass(const glm::vec2 direction);
    virtual void addMass(const float mass);
    virtual void bombAction();
    virtual void divideObject();
};

}


#endif