#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "engine/game.hpp"
#include "gameObject.hpp"

namespace agario{

class Renderer{

private:

    Game * game;

public:

    // virtual void drawGameObject(GameObject & gameObject) = 0;
    virtual void drawMap() = 0;
    Game * getGame(){return this->game;}

};

}

#endif