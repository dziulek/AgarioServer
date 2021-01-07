#include "threadFunctions.hpp"

void * clientThread(void * server_client_struct){

    server_client * sc = (server_client *)server_client_struct;
    
    Client * client = sc->server->addNewClient(sc->client_sockfd, sc->ip_addr, sc->s);
    std::cout<<"before while"<<std::endl;

    while(client->getDisconnect() == false){

        // listenOnSocket(client)
    }

    std::cout<<"after while"<<std::endl;
    pthread_exit(NULL);
}
