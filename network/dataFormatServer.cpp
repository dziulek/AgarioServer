#include "dataFormatServer.hpp"

void DataFormatServer::appendPlayer(agario::Player * player){

    this->appendChar(PLAYER);

    this->appendChar(NICKNAME);

    this->appendString("Unnamed_cell");

    this->appendChar(COORDINATES);

    for(int i = 0; i < player->getSize(); i++){

        this->appendFloat((*player)[i].getPosition().x);
        this->appendFloat((*player)[i].getPosition().y);
    }
}

void DataFormatServer::extractClientInfo(clientInfo & cinfo){

    char c;
    float x, y;
    bool b;

    int curr_ind = 0;

    c = this->getChar(curr_ind);

    this->printBuf();

    curr_ind = this->getNextIndexSeparator(curr_ind);
    x = this->getFloat(curr_ind);
    curr_ind = this->getNextIndexSeparator(curr_ind);
    y = this->getFloat(curr_ind);

    cinfo.mousePosition = {x, y};

    // curr_ind = this->getNextIndexSeparator(curr_ind);

    // c = this->getChar(curr_ind);
    // curr_ind = this->getNextIndexSeparator(curr_ind);
    // b = this->getBool(curr_ind);
    // cinfo.divide_action = b;
    // curr_ind = this->getNextIndexSeparator(curr_ind);
    // b = this->getBool(curr_ind);

    // cinfo.w_action = b;
}

void DataFormatServer::appendMinis(agario::Game * game, agario::Player * player){

    std::pair<std::pair<int, int>, std::pair<int, int>> mini_range = game->getMap()->getMiniRects(
        player->getView().first, player->getView().second
    );

    std::cout<<mini_range.first.first<<" "<<mini_range.first.second<<std::endl;
    std::cout<<mini_range.second.first<<" "<<mini_range.second.second<<std::endl;
    this->appendChar(MINIS);

    for(int i = mini_range.first.first; i < mini_range.second.first; i++){

        for(int j = mini_range.first.second; i < mini_range.second.second; i++){

            for(auto & m : game->getMap()->minis[j][i]){
                
                this->appendFloat(m.get()->getPosition().x);
                this->appendFloat(m.get()->getPosition().y);
            }    
        }
    }
}