#ifndef BOMB_HPP
#define BOMB_HPP

#include "engine/gameObject.hpp"
#include "engine/shapes/allshapes.hpp"
#include "engine/constants.hpp"

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
};

}//namespace agario




#endif