#ifndef MOUSE_OBSERVER
#define MOUSE_OBSERVER

#include "callbackObserver.hpp"
#include "renderer.hpp"

namespace agario{

using namespace shapes;

class MouseObserver : public CallbackObserver{

private:

    SFMLRenderer * renderer;

public: 

    void update() override;

};

}


#endif
