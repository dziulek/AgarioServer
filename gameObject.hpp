#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "./shapes/circle.hpp"
#include "constants.hpp"
#include "glm/glm.hpp"
#include <vector>

namespace agario{

class GameObject {

private:    

    std::vector<shapes::Circle *> sparkles;
    bool compoundAvailable = true;


    void setAlmostFinalResultantForces(const glm::vec2 cursorPos);
    void calculateFinalResultantForces(const glm::vec2 cursorPos);

public:

    size_t getSparklesSize(){ return this->sparkles.size();}
    shapes::Circle & operator[](unsigned int i);

    void setPosition(const glm::vec2 newPos);
    void move(const glm::vec2 cursorPos, const float time);
    void giveMass(const glm::vec2 direction);
    void addMass(const float mass);
    void bombAction();
    void divideObject();
};

}


#endif