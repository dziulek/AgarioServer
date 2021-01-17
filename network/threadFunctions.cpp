#include "threadFunctions.hpp"

void * clientThread(void * server_client_struct){

    server_client * sc = (server_client *)server_client_struct;
    
    Client * client = sc->server->addNewClient(sc->client_sockfd, sc->ip_addr, sc->s);

    while(client != nullptr && client->getDisconnect() == false){

        int status = sc->server->listenOnSocket(client);

        if(status == 0){
            //closed socket
            break;
        }
    }

    std::cout<<"exiting from client thread"<<std::endl;
    pthread_exit(NULL);
}

void * gameThread(void * srv){

    Server * server = (Server *)srv;

    while(server->close_server == false){

        server->gameLoop(1.0f / 30);
    }

    fprintf(stdout, "exit from game thread\n");
    pthread_exit(NULL);
}
