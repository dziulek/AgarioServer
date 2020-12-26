#ifndef CALLBACK_OBSERVER
#define CALLBACK_OBSERVER

#include "shapes/shape.hpp"
#include "SFMLRenderer.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

namespace agario{

using namespace shapes;

class CallbackObserver{

private: 

    SFMLRenderer * renderer;

public:

    virtual void update() = 0;
    SFMLRenderer * getRenderer(){ return this->renderer;}

};

}

#endif