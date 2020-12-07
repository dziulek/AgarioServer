#ifndef TESTMAP_HPP
#define TESTMAP_HPP

#include "map.hpp"
#include <vector>

namespace agario{

class TestMap : Map{

public:
    int width;
    int height;
    const int cellWidth = 10;

    TestMap() : width(1000), height(500){}
    TestMap(int w, int h) : width(w), height(h){}
    
};    

}


#endif