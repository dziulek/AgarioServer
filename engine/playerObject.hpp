#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "shapes/allshapes.hpp"
#include "gameObject.hpp"
#include <vector>
#include <memory>
#include <iostream>

namespace agario{

using namespace shapes;

class PlayerObject : public GameObject{

private:

    std::vector<std::unique_ptr<MoveableCircle>> blobs;
    float totalArea;

    void setVelocities();

public:

    glm::vec2 mousePosition;

    PlayerObject(glm::vec2 pos){

        blobs.push_back(std::unique_ptr<MoveableCircle>(new MoveableCircle(pos, MIN_PLAYER_RADIUS)));

        totalArea = blobs[0].get()->getArea();
    }
    virtual ~PlayerObject(){}

    MoveableCircle & operator[](int t);

    void divideObject() override;
    void addMass(const float mass) override;
    void move(const float dTime) override;
    void setPosition(const glm::vec2 pos) override;

    float bombAction();
    float getTotalArea();
    int getSize();
};

}


#endif