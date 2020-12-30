#include "game.hpp"


namespace agario{

using namespace shapes;

void Game::mainLoop(const float dTime){

    //move players
    for(int i = 0; i < players.size(); i++){
        players[i].get()->move(dTime);
    }
}

void Game::addPlayer(){

    players.push_back(std::unique_ptr<Player>(new Player(glm::vec2(map->width, map->height), "test")));
}

}