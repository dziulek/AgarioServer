#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string.h>

class Client{
    
private:

    char * ip_addr;
    int sockfd;
    struct sockaddr_storage myInfo;

public:

    Client(const char * ip_addr, int sockfd, struct sockaddr_storage s) : sockfd(sockfd){

        myInfo = s;
        strcpy(this->ip_addr, ip_addr);
    }
    ~Client(){}

    char * getIp_addr(){ return ip_addr;}
    int getSockfd(){ return sockfd;}
    void * getInfo(){ return &this->myInfo;}
};

#endif