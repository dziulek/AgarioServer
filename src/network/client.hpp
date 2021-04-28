#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../../lib/AgarioEngine/src/agario_engine.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <vector>
#include <memory>
/*
Klasa Client reprezentuje klienta na serwerze, 
jeden klient jest powiązany z tylko jednym zawodnikiem
*/
class Client{
    
private:

    char ip_addr[INET_ADDRSTRLEN];//adres ip
    int sockfd;//numer gniazda
    struct sockaddr_storage * myInfo;//struktura zawierająca dane o kliencie
    agario::Player * player;//wskaźnik na gracza
    agario::Game * game;//wskaźnik go gry
    bool disconnect = false;//zmienna aktualnie nie używana

    pthread_t thread_id;//id wątku klienta

public:

    Client(char * ip_addr, int sockfd, struct sockaddr_storage * s) : sockfd(sockfd){

        myInfo = s;
        strcpy(this->ip_addr, ip_addr);
    }
    ~Client(){}

    char * getIp_addr(){ return ip_addr;}
    int getSockfd(){ return sockfd;}
    void * getInfo(){ return &this->myInfo;}
    void setThreadId(pthread_t thread_id){ thread_id = thread_id;}
    pthread_t & getThreadId(){ return this->thread_id;}
    
    void setPlayer(agario::Player * player){ this->player = player;}
    agario::Player * getPlayer(){ return this->player;}
    void setGame(agario::Game * game){ this->game = game;}
    agario::Game * getGame(){ return this->game;}
    void setDisconnect(){ this->disconnect = true;}
    bool getDisconnect(){ return this->disconnect;}
};

#endif