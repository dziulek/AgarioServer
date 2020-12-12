#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "./maps/testMap.hpp"
#include "./maps/classicMap.hpp"
#include "gameObject.hpp"

namespace agario{

class Renderer{


public:

    virtual void drawGameObject(GameObject & gameObject);
    virtual void drawMap(TestMap & map);
    virtual void drawMap(ClassicMap & classicMap);

};

}

#endif