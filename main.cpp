#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "src/network/server.hpp"


#include "lib/json/single_include/nlohmann/json.hpp"

using namespace agario;
using namespace nlohmann;

int main(){

    Server server;

    server.mainLogic();   

    return 0;
}