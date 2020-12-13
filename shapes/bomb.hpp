#ifndef BOMB_HPP
#define BOMB_HPP

#include "shape.hpp"
#include "constants.hpp"
namespace agario{

namespace shapes{

class Bomb : public Shape{

private:
    int nOfIdents;
    float radius;

public:

    Bomb(){
        nOfIdents = 30;
        radius = 2 * MIN_RADIUS;
    }
    int getNOfIdents(){ return nOfIdents;}
    float getRadius(){ return radius;}
};

}//namespace shapes

}//namespace agario




#endif