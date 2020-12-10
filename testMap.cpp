#include "testMap.hpp"

namespace agario{

using namespace shapes;

void TestMap::addGameObject(GameObject & gameObject){

    auto pos = findPlaceForNewPlayer();
    gameObject.setPosition(pos);

    this->gameObj.push_back(&gameObject);
}

void TestMap::addBomb(){

    auto pos = findPlaceForBomb();
    Bomb * bomb = new Bomb();

    bomb->setPosition(pos);

    this->bombs.push_back(bomb);
}

void TestMap::addMini(){

    auto pos = findPlaceForMini();

    Mini * mini = new Mini();
    mini->setPosition(pos);

    this->minis.push_back(mini);
}

}