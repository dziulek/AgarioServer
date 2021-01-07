#include "game.hpp"


namespace agario{

using namespace shapes;

void Game::mainLoop(const float dTime){

    //move players
    for(int i = 0; i < 1; i++){
        players[i].get()->move(dTime);
    }
}

Player * Game::addPlayer(){

    players.push_back(std::unique_ptr<Player>(new Player(glm::vec2(map->width/2, map->height/2), "test")));
    map->addPlayerObject(players.back().get());
    nOfPlayers++;

    return this->players.back().get();
}

}