#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "playerObject.hpp"
#include <vector>
#include <string>

namespace agario{

using namespace shapes;

class Player : public PlayerObject{

private:

    std::string nick = "";
    float mass;
    float highestScore;
    int highestPosition;

public:

    Player(const glm::vec2 pos) : PlayerObject(pos){

        
    }

};

}

#endif