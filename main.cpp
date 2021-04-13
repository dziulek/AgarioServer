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

    // Server server;

    // server.mainLogic();   

    json j;

    std::vector<int> a = {1,2,3,4,5};

    j["player"]["blobs"]["x"] = a;

    std::string s = j.dump();
    std::cout << s << std::endl;

    auto t = j["map"].get<int>();
        std::cout << "t is null" <<std::endl;
    std::cout << t <<std::endl;

    return 0;
}