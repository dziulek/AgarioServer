#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "src/network/server.hpp"


using namespace agario;

int main(){

    Server server;

    server.mainLogic();   

    return 0;
}