#ifndef MOUSE_OBSERVER
#define MOUSE_OBSERVER

#include "callbackObserver.hpp"
#include "renderer.hpp"

namespace agario{

using namespace shapes;

class MouseObserver : public CallbackObserver{

public: 

    MouseObserver(SFMLRenderer * rend) : CallbackObserver(rend){

        
    }
    void update(Player * player) override;

};

}


#endif
