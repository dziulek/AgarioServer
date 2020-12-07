#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "map.hpp"
#include "gameObject.hpp"

namespace agario{

class Renderer{

public:

    virtual void drawGameObject(const GameObject & gameObject);
    virtual void drawMap(const Map & map);

};

}

#endif