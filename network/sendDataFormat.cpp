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

            while(++index < strlen(buf) && buf[index] != SEPARATOR);

            if(index == strlen(buf)){
                //error
            }

            else {
                int len = index - cp_index - 1;
                char local[len];
                bzero(local, sizeof(local));

                memcpy(local, this->buf + cp_index + 1, len);

                out = (float)atof(local);
                return out;
            }
        }
    }
    return 0.0f;
}

char SendDataFormat::getChar(int index){

    if(index < 0 || index > 1 + strlen(this->buf))
        return '\0';

    return this->buf[index + 1];
}

bool SendDataFormat::getBool(int index){

    if(index < 0 || index > 1 + strlen(this->buf))
        return 0;

    return this->buf[index + 1] == '1' ? true : false;
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

    while(++currInd < strlen(this->buf) && buf[currInd] != SEPARATOR);

    return currInd;
}