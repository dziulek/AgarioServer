#ifndef CLIENT_HPP
#define CLIENT_HPP

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

class Client{
    
private:

    char ip_addr[INET_ADDRSTRLEN];
    int sockfd;
    struct sockaddr_storage * myInfo;

    pthread_t thread_id;

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
};

#endif