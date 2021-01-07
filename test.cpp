#include "SFMLRenderer.hpp"
#include "engine/game.hpp"
#include "mouseObserver.hpp"
#include "engine/maps/mapMiniController.hpp"
#include "engine/maps/mapCrashController.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "network/server.hpp"


using namespace agario;

int main(){

    Server server;

    int status = server.mainLogic();

    if(status == -1){
        return -1;
    }

    return 0;
}