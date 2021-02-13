#include "moveableCircle.hpp"

namespace agario{

namespace shapes{

void MoveableCircle::setVelocity(const glm::vec2 v){

    this->velocity = v;
}

const glm::vec2 MoveableCircle::getVelocity() const{

    return this->velocity;
}

void MoveableCircle::move(const float dTime){

    centerPosition += dTime * velocity;
    // std::cout << glm::length(velocity) <<std::endl;
}

std::pair<glm::vec2, glm::vec2> MoveableCircle::calculateGravityVelocities(const MoveableCircle & c1, const MoveableCircle & c2){

    glm::vec2 r = c2.getPosition() - c1.getPosition();

    float len = glm::length(r);
    if(len < c1.getRadius() + c2.getRadius() - eps){

        return {c1.getVelocity(), c2.getVelocity()};
    }

    glm::vec2 v1 = c1.calculateVelocityMod() * r;

    r = -r;
    glm::vec2 v2 = c2.calculateVelocityMod() * r;

    return {v1, v2};
}

void MoveableCircle::addMass(const float mass){

    this->area += mass;
    float r = this->getRadiusFromArea();
    this->radius = r;
}

}

}