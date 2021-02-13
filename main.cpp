#include "engine/game.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "network/server.hpp"


using namespace agario;

int main(){

    srand(time(NULL));

    Server server;

    server.mainLogic();   

    return 0;
}