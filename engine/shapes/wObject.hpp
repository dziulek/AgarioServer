#ifndef W_OBJECT_HPP
#define W_OBJECT_HPP

#include "shape.hpp"
#include "moveableCircle.hpp"

namespace agario{

namespace shapes{

class WObject : public MoveableCircle{

private:

    bool isMove = true;
    bool checkIfStop();
    float time;
    glm::vec2 accelerationFunction();


public:

    WObject(glm::vec2 pos, glm::vec2 dir) : MoveableCircle(pos, MIN_PLAYER_RADIUS){
        
        this->velocity = glm::normalize(dir);
        this->velocity *= 2.0f * calculateVelocityMod();
        this->acceleration = glm::normalize(dir);
        this->time = 0.0f;
    }

    void stopObject();
    void slowDown();
    void move(const float dTime) override;

};

}//shapes

}//agario


#endif