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

    std::cout<<"exit from client thread"<<std::endl;
    pthread_exit(NULL);
}

void * gameThread(void * srv){

    Server * server = (Server *)srv;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while(server->close_server == false){

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        int delta = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        begin = std::chrono::steady_clock::now();
        server->gameLoop(static_cast<float>(delta) * 1e-6);
    }

    fprintf(stdout, "exit from game thread\n");
    pthread_exit(NULL);
}
