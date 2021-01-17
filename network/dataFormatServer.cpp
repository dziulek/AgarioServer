#include "dataFormatServer.hpp"

void DataFormatServer::appendPlayer(agario::Player * player){

    this->appendChar(PLAYER);

    this->appendChar(NICKNAME);

    this->appendString("Unnamed cell");

    this->appendChar(COORDINATES);

    for(int i = 0; i < player->getSize(); i++){

        this->appendFloat((*player)[i].getPosition().x);
        this->appendFloat((*player)[i].getPosition().y);
    }

    this->appendSeparator();
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