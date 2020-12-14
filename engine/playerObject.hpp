#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "shapes/shape.hpp"
#include "allshapes.hpp"
#include "gameObject.hpp"
#include <vector>

namespace agario{

using namespace shapes;

class PlayerObject : public GameObject{

private:

    std::vector<MoveableCircle *> blobs;
    float totalArea;

public:

    PlayerObject(const glm::vec2 pos){
        
        MoveableCircle * mc = new MoveableCircle(pos, MIN_PLAYER_RADIUS);

        blobs.push_back(mc);

        totalArea = mc->getRadius();
    }

    void divideGameObject() override;
    void addMass() override;
    void move() override;
    void setPosition() override;

    float getTotalArea();
};

}


#endif