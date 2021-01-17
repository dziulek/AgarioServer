#include "game.hpp"


namespace agario{

using namespace shapes;

void Game::mainLoop(const float dTime){

    for(auto & player : players){

        player->setVelocities();
    }
    map->notify();
    
    // //move players
    // for(int i = 0; i < 1; i++){
    //     players[i].get()->move(dTime);
    // }
}

Player * Game::addPlayer(std::string nickname){

    players.push_back(std::unique_ptr<Player>(new Player(map->findPositionForNewPlayer(), nickname)));
    map->addPlayerObject(players.back().get());
    nOfPlayers++;

    return this->players.back().get();
}

void Game::deletePlayer(Player * player){

    player = nullptr;

    cullDeadPlayers();
}

void Game::cullDeadPlayers(){

    for(int i = 0; i < players.size(); i++){

        if(players[i].get() == nullptr){

            players[i].reset();
            players[i] = std::move(players.back());
            players.pop_back();

            i--;
        }
    }
}

}