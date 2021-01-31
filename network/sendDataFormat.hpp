#ifndef SEND_DATA_FORMAT_HPP
#define SENT_DATA_FORMAT_HPP

#include "../engine/glm/glm.hpp"

#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define SEPARATOR ':'
#define MAX_LEN_BUFER 100000
#define N_CHAR_FLOAT 10

#define PLAYER 'p'
#define MYPLAYER 'u'
#define STATE 's'
#define PLAY_IN 'i'
#define PLAY_OUT 'o'
#define NICKNAME 'n'
#define MAP 'm'
#define MINIS 'q'
#define COORDINATES 'c'
#define MOUSE 'm'
#define DIVIDE_ACTION 'd'
#define W_MASS 'w'
#define VIEW 'v'
#define MASS 'r'


struct clientInfo{

    char state;
    glm::vec2 mousePosition;
    bool divide_action;
    bool w_action;
};

struct serverToClient{

};

class SendDataFormat{
    
protected:

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
    char getChar(int index);
    int getNextIndexSeparator(int currInd);
    bool getBool(int currInd);


    void appendMouseCoordinates(float x, float y);
};

#endif