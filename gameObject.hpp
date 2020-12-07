#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "shape.hpp"
#include "circle.hpp"
#include <glm.hpp>
#include <vector>

namespace agario{

class GameObject {

private:    

    std::vector<shapes::Circle *> sparkles;
    bool compoundAvailable = true;


    void setAlmostResultantForces(const glm::vec2 cursorPos);
    void calculateFinalResultantForces(const glm::vec2 cursorPos);

public:

    void setPosition(const glm::vec2 newPos);
    void move(const glm::vec2 cursorPos, const float time);
    void giveMass(const glm::vec2 direction);
    void addMass(const float mass);
    void bombAction();
    void divideObject();
};

}


#endif