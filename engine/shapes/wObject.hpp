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


public:

    WObject(glm::vec2 pos, glm::vec2 dir) : MoveableCircle(pos, MIN_PLAYER_RADIUS){
        
        this->velocity = glm::normalize(dir);
        this->velocity *= calculateVelocityMod();
        this->acceleration = this->velocity * 4.0f * W_ACCELERATION_VALUE;
    }

    void stopObject();
    void slowDown();
    void move1(const float dTime);

};

}//shapes

}//agario


#endif