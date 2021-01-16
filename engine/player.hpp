#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "playerObject.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>

namespace agario{

using namespace shapes;

class Player : public PlayerObject{

private:

    char state;
    std::string nick = "";
    float mass;
    float highestScore;
    int highestPosition;

public:

    Player(glm::vec2 pos, std::string nickname) : PlayerObject(pos){
        
        nick = nickname;
    }
    virtual ~Player(){}
    char getState(){ return state;}
    void setState(char s){this->state = s;}
    std::pair<glm::vec2, glm::vec2> getView();

};

}

#endif