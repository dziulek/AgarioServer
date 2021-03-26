#ifndef BOMB_HPP
#define BOMB_HPP

#include "gameObject.hpp"
#include "allshapes.hpp"
#include "constants.hpp"

namespace agario{

using namespace shapes;

class Bomb : public GameObject{

private:
    
    MoveableCircle  * bomb;

public:

    Bomb(const glm::vec2 position){
        MoveableCircle * b = new MoveableCircle(position, BOMB_RADIUS);

        bomb = b;
    }

    void setRadius(const float r){ this->bomb->setRadius(r);}
    const float getRadius() const { return this->bomb->getRadius();}
    void setPosition(const glm::vec2 position) override;
    void addMass(const float mass) override;
    void move(const float dTime) override;
    void divideObject() override;

    float getXCoord(){return this->bomb->getPosition().x;}
    float getYCoord(){return this->bomb->getPosition().y;}
    float getArea(){return this->bomb->getArea();}
    glm::vec2 getPosition(){return this->bomb->getPosition();}
};

}//namespace agario




#endif