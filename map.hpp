#ifndef MAP_HPP
#define MAP_HPP

#include "gameObject.hpp"
#include "mini.hpp"
#include "bomb.hpp"
#include <vector>

namespace agario{

class Map{

protected:

    std::vector<GameObject *> gameObj;
    std::vector<shapes::Bomb *> bombs;
    std::vector<const shapes::Mini *> minis;

public:
    
    void addGameObject(GameObject & gameObject){
        this->gameObj.push_back(&gameObject);
    }
    void addBomb(shapes::Bomb & bomb){
        this->bombs.push_back(&bomb);
    }
    void addMini(shapes::Mini & mini){
        this->minis.push_back(&mini);
    }


};

}


#endif