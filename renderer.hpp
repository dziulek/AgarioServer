#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "game.hpp"
#include "gameObject.hpp"

namespace agario{

class Renderer{

private:

    Game * game;

public:

    virtual void drawGameObject(GameObject & gameObject) = 0;
    virtual void drawMap(const Map * map) = 0;
    Game * getGame(){return this->game;}

};

}

#endif