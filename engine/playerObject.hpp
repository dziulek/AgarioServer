#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "shapes/shape.hpp"
#include "shapes/allshapes.hpp"
#include "gameObject.hpp"
#include <vector>

namespace agario{

using namespace shapes;

class PlayerObject : public GameObject{

private:

    std::vector<agario::shapes::MoveableCircle *> blobs;
    float totalArea;

public:

    PlayerObject(const glm::vec2 pos){
        
        agario::shapes::MoveableCircle * mc = new agario::shapes::MoveableCircle(pos, MIN_PLAYER_RADIUS);

        blobs.push_back(mc);

        totalArea = mc->getRadius();
    }

    agario::shapes::MoveableCircle & operator[](int t);

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