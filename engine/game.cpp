#include "game.hpp"


namespace agario{

using namespace shapes;

void Game::mainLoop(const float dTime){
    
    for(auto & player : players){

        player->setVelocities();
    }
    map->notify();
    
    // move other shapes
    for(auto & shape : this->map->abandoned){
        if(shape.get() != nullptr){
            shape.get()->move(dTime);
        }
    }
    // move players
    for(int i = 0; i < players.size(); i++){
        if(players[i].get()->getSize() > 0)
            players[i].get()->move(dTime);
    }

}

Player * Game::addPlayer(std::string nickname){

    players.push_back(std::unique_ptr<Player>(new Player(map->findPositionForNewPlayer(), nickname)));
    map->addPlayerObject(players.back().get());
    nOfPlayers++;

    return this->players.back().get();
}

void Game::deletePlayer(Player * player){

    player->setState(false);

    cullDeadPlayers();
}

void Game::cullDeadPlayers(){

    for(int i = 0; i < players.size(); i++){

        if(players[i].get()->getState() == '0'){

            players[i].reset();
            players[i] = std::move(players.back());
            players.pop_back();

            i--;
        }
    }
}

void Game::wAction(Player * player){

    this->map->wAction(player);
}

}