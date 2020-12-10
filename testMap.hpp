#ifndef TESTMAP_HPP
#define TESTMAP_HPP

#include "map.hpp"
#include "shape.hpp"
#include <vector>

namespace agario{

using namespace shapes;

class TestMap : Map{

private:

    std::vector<GameObject *> gameObj;
    std::vector<Bomb *> bombs;
    std::vector<const Mini *> minis;

public:

    float width;
    float height;
    const float cellWidth = 10;

    TestMap() : width(1000), height(500){}
    TestMap(int w, int h) : width(w), height(h){}

    std::vector<GameObject *> & getGameObjIterator(){ return this->gameObj;}
    std::vector<Bomb *> & getBombIterator(){ return this->bombs;}
    std::vector<const Mini *> & getMiniIterator(){ return this->minis;}

    void addGameObject(GameObject & gameObject) override;
    void addBomb() override;
    void addMini() override;
    
};    

}


#endif