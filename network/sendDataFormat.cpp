#include "sendDataFormat.hpp"

std::string SendDataFormat::getAsString(){
    
    return std::string(this->buf);
}

void SendDataFormat::appendSeparator(){
    
    this->buf[strlen(this->buf)] = SEPARATOR;
}
void SendDataFormat::appendFloat(float f){
    
    char local[N_CHAR_FLOAT];
    bzero(local, sizeof(local));
    int status = snprintf(local, sizeof(local), "%f", f);
    
    if(status < 0){
        
    }
    else {
        
        memcpy(this->buf + strlen(this->buf), local, sizeof(local));
    }
    this->appendSeparator();
}
void SendDataFormat::appendChar(char c){
    
    this->buf[strlen(this->buf)] = c;
    this->appendSeparator();
}

void SendDataFormat::appendString(std::string s){

     char local[s.length()];

    memcpy(this->buf + strlen(buf), local, sizeof(local));

    this->appendSeparator();
}

void SendDataFormat::clearBuf(){
    
    bzero(this->buf, MAX_LEN_BUFER);
}

void SendDataFormat::printBuf(){
    
    printf("%s\n", this->buf);
}

int SendDataFormat::getLen(){
    
    return strlen(this->buf);
}

float SendDataFormat::getFloat(int index){

    if(buf[index] != SEPARATOR) return 0.0f;

    float out;
    int cp_index = index;

    if(index < strlen(this->buf)){

        if(this->buf[index] == SEPARATOR){

            while(index < strlen(buf) && buf[index] != SEPARATOR)
                index++;

            if(index == strlen(buf)){
                //error
            }

            else {
                
                int len = index - cp_index - 1;
                char local[len];

                memcpy(local, this->buf + cp_index + 1, len);
                
                return (float)atof(local);
            }
        }
    }
    return 0.0f;
}

void SendDataFormat::appendPlayer(agario::Player * player){

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

void SendDataFormat::appendMouseCoordinates(float x, float y){

    this->appendChar(MOUSE);
    this->appendFloat(x);
    this->appendFloat(y);

    this->appendSeparator();
}

int SendDataFormat::getNextIndexSeparator(int currInd){

    if(currInd < 0 || currInd > strlen(this->buf))
        return -1;

    while(currInd < strlen(this->buf) && ++currInd != SEPARATOR);

    return currInd;
}