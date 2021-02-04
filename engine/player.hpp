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

    bool state = false;
    std::string nick = "";
    float mass;
    float highestScore;
    int highestPosition;
    uint32_t color = WHITE;

public:

    Player(glm::vec2 pos, std::string nickname) : PlayerObject(pos){
        
        nick = nickname;
        state = true;
    }
    virtual ~Player(){}
    char getState(){ return (state == true ? '1' : '0');}
    void setState(bool s){this->state = s;}
    void setNickname(std::string nickname){ this->nick = nickname;}
    std::string & getNickname(){ return this->nick;}
    std::pair<glm::vec2, glm::vec2> getView();
    void setColor();
    uint32_t getColor(){ return this->color;}

};

}

#endif