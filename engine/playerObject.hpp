#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "allshapes.hpp"
#include "gameObject.hpp"
#include "maps/map.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <utility>

namespace agario{

using namespace shapes;

class PlayerObject : public GameObject{

private:

    std::vector<std::unique_ptr<MoveableCircle>> blobs;
    float totalArea;

    

public:

    glm::vec2 mousePosition;

    PlayerObject(glm::vec2 pos){

        blobs.push_back(std::unique_ptr<MoveableCircle>(new MoveableCircle(pos, MIN_PLAYER_RADIUS)));

        totalArea = blobs.back().get()->getArea();
    }
    virtual ~PlayerObject(){}

    MoveableCircle & operator[](int t);

    std::vector<std::unique_ptr<MoveableCircle>> * getBlobs(){ return &blobs; }

    void deleteIthElement(int i);

    void setVelocities();

    void divideObject() override;
    void addMass(const float mass) override;
    void addMass(const float mass, int mcIndex);
    void move(const float dTime) override;
    void setPosition(const glm::vec2 pos) override;
    std::pair<glm::vec2, glm::vec2> getMinRectangle();

    float bombAction();
    float getTotalArea();
    int getSize();
};

}


#endif