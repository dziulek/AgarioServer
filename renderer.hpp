#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "map.hpp"
#include "testMap.hpp"
#include "classicMap.hpp"
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