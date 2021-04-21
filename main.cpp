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
    // std::string testJson = "{ \"happy\": true, \"pi\": 3.141 }";
    // json j = json::parse(testJson);

    // std::cout << j["happy"].get<bool>() <<std::endl;

    return 0;
}