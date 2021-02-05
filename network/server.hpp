#ifndef SERVER_HPP
#define SERVER_HPP

#include "../engine/agario_engine.hpp"
#include "threadFunctions.hpp"
#include "client.hpp"
#include "constants.hpp"
#include "dataFormatServer.hpp"

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
#include <ctime>
#include <chrono>
#include <fcntl.h>
#include <cmath>

class Server;

typedef void * (*THREADFUNCPTR)(void *);

struct recvDataFormat{

    char state;
    bool w_action;
    bool divide_action;
    int mouse_coordinates[2];
};


//struktura potrzebna do tworzenia wątku dla nowego klienta
struct server_client{
    Server * server;
    char * ip_addr;
    int client_sockfd;
    sockaddr_storage * s;
};


class Server{

private:

    std::vector<std::unique_ptr<agario::Game>> games;
    std::vector<std::unique_ptr<Client>> clients;

    char portNumber[5];
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *serverInfo;
    int opt_value = 1;
    char s[INET_ADDRSTRLEN];

    bool close_server = false;
    float send_frequency = 30.0f;

    pthread_t server_thread;
    pthread_t send_thread;
    pthread_t game_thread;
    pthread_mutex_t send_data_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t client_creation_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t new_player_mutex = PTHREAD_MUTEX_INITIALIZER;

    int setUpServer();
    int sendDataToClient(Client * client);
    void * get_in_addr(struct sockaddr *sa);
    void findGameForNewClient(Client * client);
    void interpretData(recvDataFormat * data);

    static void serializeFloat(const float f, char * buf, int ind);

    static void sig_pipe_signal_handler(int signum);
    static void non_blocking_socket_signal(int signum);

    void fillDataToClient(Client * client, DataFormatServer & data);
    void * sendDataThread(void * args);
    void cullDisconnectedClients();

    void gameLoop(const float dTime);
    
public:

    Server(){
        
        signal(SIGPIPE, sig_pipe_signal_handler);

        strcpy(this->portNumber, std::string("1234").c_str());
        int status = setUpServer();
        if(status < 0){

        }
    }
    Server(std::string portNumber){
        
        int status = setUpServer();
        if(status < 0){

        }
    }

    Client * addNewClient(int sockfd, char * ip_addr, struct sockaddr_storage * s);
    int disconnectClient(int sockfd);
    void createNewGame();
    void closeServer();
    void deleteGame(std::unique_ptr<agario::Game> & game);
    void deleteGame(int gameIndex);
    void deleteEmptyGames();
    void * sendDataToClients(void * args);
    int listenOnSocket(Client * client);
    friend void * clientThread(void * server_client);
    friend void * gameThread(void * server);
    friend void * serverInfoRoutine(void * args);

    const std::time_t getServerTime();

    int mainLogic();
};




#endif