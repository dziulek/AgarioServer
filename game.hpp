#ifndef GAME_HPP
#define GAME_HPP

#include "./maps/testMap.hpp"
#include "./maps/classicMap.hpp"

namespace agario{

class Game{

private:

    TestMap map;

public:

    TestMap & getMap(){ return map;}
};

}

#endif