#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

namespace agario{

class Map{
protected:

    std::vector<GameObject *> gameObj;
    std::vector<Bomb *> bombs;
    std::vector<Mini *> minis;

public:
    

};

}


#endif