#ifndef SERVER_HPP
#define SERVER_HPP

#include "../engine/agario_engine.hpp"
#include "client.hpp"

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

class Server{

private:

    std::vector<std::unique_ptr<agario::Game>> games;
    std::vector<std::unique_ptr<Client>> clients;

    const char * portNumber;
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *serverInfo;
    int opt_value = 1;
    char s[INET_ADDRSTRLEN];

    int setUpServer(const std::string portNumber = "");
    int sendDataToClient(Client * client);
    void * get_in_addr(struct sockaddr *sa);
    
public:

    Server(){

        int status = setUpServer();
        if(status < 0){

        }
    }
    Server(const std::string portNumber){
        
        int status = setUpServer(portNumber);
        if(status < 0){

        }
    }

    int addNewClient(int sockfd, const char * ip_addr, struct sockaddr_storage s);
    int disconnectClient(int sockfd);
    void createNewGame();
    void closeServer();
    void deleteGame(agario::Game * game);
    void deleteEmptyGames();
    void sendDataToClients();

    int mainLogic();
};




#endif