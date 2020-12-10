#ifndef MAP_HPP
#define MAP_HPP

#include "gameObject.hpp"
#include "mini.hpp"
#include "bomb.hpp"
#include <vector>

namespace agario{

class Map{

private:

    virtual glm::vec2 findPlaceForBomb();
    virtual glm::vec2 findPlaceForMini();
    virtual glm::vec2 findPlaceForNewPlayer();

protected:

    std::vector<GameObject *> gameObj;
    std::vector<shapes::Bomb *> bombs;
    std::vector<const shapes::Mini *> minis;

public:
    
    virtual void addGameObject(GameObject & gameObject);
    virtual void addBomb();
    virtual void addMini(shapes::Mini & mini);
    
};

}


#endif