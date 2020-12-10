#include "map.hpp"

namespace agario{

using namespace shapes;

void Map::addGameObject(const GameObject & gameObject){

    auto pos = findPlaceForNewPlayer();
    gameObject.setPosition(pos);

    this->gameObj.push_back(gameObject);
}

void Map::addBomb(){

    auto pos = findPlaceForBomb();
    Bomb bomb * = new Bomb();

    bomb.setPosition(pos);

    this->bombs.push_back(bomb);

}

void Map::addMini(){

    auto pos = findPlaceForMini();

    Mini mini * = new Mini();
    mini.setPosition(pos);

    this->minis.push_back(mini);
}
}