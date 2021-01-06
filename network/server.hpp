#ifndef SERVER_HPP
#define SERVER_HPP

#include "../engine/agario_engine.hpp"
#include "client.hpp"
#include "constants.hpp"

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
#include <map>

typedef void * (*THREADFUNCPTR)(void *);

struct sendDataFormat{

    std::vector<std::map<std::string, float, float>> coordinates;
};

struct recvDataFormat{

    int mouse_coordinates[2];
};


class Server{

private:

    std::vector<std::unique_ptr<agario::Game>> games;
    std::vector<std::unique_ptr<Client>> clients;

    char * portNumber;
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *serverInfo;
    int opt_value = 1;
    char s[INET_ADDRSTRLEN];

    pthread_t server_thread;

    int setUpServer();
    int sendDataToClient(Client * client);
    void * get_in_addr(struct sockaddr *sa);
    void findGameForNewClient(Client * client);
    void interpretData(void * data);

    void * serverInfoRoutine(void * args);
    
public:

    Server(){
        
        strcpy(this->portNumber, "1234");
        int status = setUpServer();
        if(status < 0){

        }
    }
    Server(std::string portNumber){
        
        int status = setUpServer();
        if(status < 0){

        }
    }

    int addNewClient(int sockfd, char * ip_addr, struct sockaddr_storage * s);
    int disconnectClient(int sockfd);
    void createNewGame();
    void closeServer();
    void deleteGame(std::unique_ptr<agario::Game> & game);
    void deleteGame(int gameIndex);
    void deleteEmptyGames();
    void sendDataToClients();
    void * listenOnSocket(void * client);

    int mainLogic();
};




#endif