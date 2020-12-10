#ifndef MAP_HPP
#define MAP_HPP

#include "gameObject.hpp"
#include "mini.hpp"
#include "bomb.hpp"
#include <vector>

namespace agario{

using namespace shapes;

class Map{

protected:

    virtual glm::vec2 findPlaceForBomb();
    virtual glm::vec2 findPlaceForMini();
    virtual glm::vec2 findPlaceForNewPlayer();

public:
    
    virtual void addGameObject(GameObject & gameObject) = 0;
    virtual void addBomb() = 0;
    virtual void addMini() = 0;
    
};

}


#endif