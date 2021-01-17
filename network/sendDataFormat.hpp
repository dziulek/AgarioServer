#ifndef SEND_DATA_FORMAT_HPP
#define SENT_DATA_FORMAT_HPP

#include "engine/agario_engine.hpp"

#include <string>
#include <string.h>
#include <stdlib.h>

#define SEPARATOR ':'
#define MAX_LEN_BUFER 1000
#define N_CHAR_FLOAT 10

#define PLAYER 'p'
#define NICKNAME 'n'
#define MAP 'm'
#define COORDINATES 'c'
#define MOUSE 'm'


class SendDataFormat{
    
private:

    char buf[MAX_LEN_BUFER];
    
public:

    SendDataFormat(){
        bzero(buf, sizeof(buf));
        buf[0] = SEPARATOR;
    }
    std::string getAsString();
    
    char * getBuf(){ return this->buf;}

    void appendSeparator();
    void appendFloat(float f);
    void appendChar(char c);
    void appendString(std::string s);
    void clearBuf();
    void printBuf();
    int getLen();
    float getFloat(int index);
    int getNextIndexSeparator(int currInd);

    void appendPlayer(agario::Player * player);
    void appendMouseCoordinates(float x, float y);
};

#endif