#ifndef CALLBACK_OBSERVER
#define CALLBACK_OBSERVER

#include "SFMLRenderer.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

namespace agario{

using namespace shapes;

class CallbackObserver{

protected: 

    SFMLRenderer * renderer;

public:

    CallbackObserver(SFMLRenderer *rend) : renderer(rend){}
    virtual void update(Player * player) = 0;
    SFMLRenderer * getRenderer(){ return this->renderer;}

};

}

#endif