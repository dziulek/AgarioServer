#include "server.hpp"

int Server::setUpServer(){

    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(NULL, this->portNumber, &hints, &serverInfo)) != 0){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return -1;
    }

    sockfd = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

    if((sockfd < 0)){
        fprintf(stderr, "creating socket error: %s\n", gai_strerror(status));
        return -1;
    }

    if((status = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_value, sizeof(int))) < 0){
        fprintf(stderr, "setsockopt error: %s\n", gai_strerror(status));
        return -1;
    }

    if((status = bind(sockfd, serverInfo->ai_addr, serverInfo->ai_addrlen)) < 0){
        fprintf(stderr, "bind error: %s\n", gai_strerror(status));
        return -1;
    }

    if((status = listen(sockfd, 5)) != 0){
        fprintf(stderr, "listen error: %s\n", gai_strerror(status));
        return -1;
    }

    freeaddrinfo(serverInfo);
}

Client * Server::addNewClient(int sockfd, char * ip_addr, struct sockaddr_storage * s){

    std::unique_ptr<Client> new_client = std::unique_ptr<Client>(new Client(ip_addr, sockfd, s));
    clients.push_back(std::move(new_client));
    findGameForNewClient(clients.back().get());

    fprintf(stdout, "log: new client, ip = %s, socket descriptor = %d\n", ip_addr, sockfd);


    return clients.back().get();
}

int Server::disconnectClient(int sockfd){

    fprintf(stdout, "log: disconnecting client, socket = %d\n", sockfd);
    close(sockfd);
}

void Server::createNewGame(){

    games.push_back(std::unique_ptr<agario::Game>(new agario::Game()));
}

void Server::deleteGame(std::unique_ptr<agario::Game> & game){

    game.reset();
    game = std::move(games.back());
    games.pop_back();
}

void Server::deleteGame(int gameIndex){

    games[gameIndex].reset();
    games[gameIndex] = std::move(games.back());
    games.pop_back();
}

void Server::deleteEmptyGames(){

    for(auto & g : games){

        if(g.get()->getnOfPlayers() == 0){

            deleteGame(g);
        }
    }
}

void * Server::sendDataToClients(void * args){

    pthread_mutex_lock(&send_data_mutex);

    for(auto & c : clients){

        // int status = sendDataToClient(c.get());

        // if(status < 0){

        // }
    }

    pthread_mutex_unlock(&send_data_mutex);
}

void * Server::sendDataThread(void * args){

    while(close_server == false){

        sendDataToClients(NULL);
    }

    pthread_exit(NULL);
}

void Server::fillDataToClient(Client * client, sendDataFormat & sendData){

    bzero(&sendData, sizeof(sendData));
    //check state
    sendData.state = client->getPlayer()->getState();
    
    //player coordinates
    for(int i = 0; i < client->getPlayer()->getSize(); i++){

        sendData.player_coordinates[i][0] = (*client->getPlayer())[i].getPosition().x;
        sendData.player_coordinates[i][1] = (*client->getPlayer())[i].getPosition().y;
    }
    //other players coordinates

    //minis coordinates
    // for(int i = 0; i < std::min(100, client->getGame()->getMap()->nOfMinis); i++){

        
    // }

    //bomb coordinates
}

int Server::sendDataToClient(Client * client){

    sendDataFormat sendData;
    fillDataToClient(client, sendData);

    int status = write(client->getSockfd(), (void *)&sendData, sizeof(sendData));

    if(status == -1){

        fprintf(stdout, "cannot send data to client under %s, error: %s\n", client->getIp_addr(), gai_strerror(status));
    }

}

int Server::mainLogic(){

    int status = pthread_create(&this->server_thread, NULL,  (THREADFUNCPTR) &Server::serverInfoRoutine, this);

    if(status){

        fprintf(stderr, "creating server thread: %s", gai_strerror(status));
        return -1;
    }

    status = pthread_create(&this->send_thread, NULL, (THREADFUNCPTR) &Server::sendDataThread, this);

    if(status){

        fprintf(stderr, "creating send data thread: %s", gai_strerror(status));
        return -1;
    }

    struct sockaddr_storage client_addr;
    socklen_t str_size = sizeof(client_addr);

    while(close_server == false){

        int client_sockfd = accept(this->sockfd, (struct sockaddr *)&client_addr, &str_size);
        if(client_sockfd == -1){

            fprintf(stderr, "accept client: %s\n", gai_strerror(client_sockfd));
            return -1;
        }

        char s[INET_ADDRSTRLEN];
        inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), s, sizeof(s));
        
        pthread_t client_thread;

        server_client sc;
        sc.server = this;
        sc.ip_addr = s;
        sc.client_sockfd = client_sockfd;
        //struct sockaddr_storage temporarily unnecessary

        status = pthread_create(&client_thread, NULL, clientThread, (void *)&sc);

        if(status){

            fprintf(stderr, "creating new thread for a client: %s\n", gai_strerror(status));

        }
    }

    pthread_join(this->server_thread, NULL);
    pthread_join(this->send_thread, NULL);

    for(auto & c : clients){

        pthread_join(c.get()->getThreadId(), NULL);
    }
    closeServer();
}

void * Server::get_in_addr(struct sockaddr *sa){

    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void Server::closeServer(){

    close(this->sockfd);
}

void Server::findGameForNewClient(Client * client){

    bool added = false;
    for(auto & g : games){

        if(g.get()->getnOfPlayers() < 5){

            agario::Player * p = g.get()->addPlayer();
            client->setPlayer(p);
            added = true;
            break;
        }
        
    }

    if(added = false){

        this->createNewGame();

        agario::Player * p = games.back().get()->addPlayer();
        client->setPlayer(p);
    }
}

void Server::interpretData(recvDataFormat * data){


}

void * Server::listenOnSocket(void * client){

    Client * c = (Client *)client;
    bool client_is_there = 1;

    struct recvDataFormat recvData;

    while(c->getDisconnect() == false){

        int n = read((long)c->getSockfd(), (void *)&recvData, sizeof(recvData));

        if(n == 0){
            //closed socket
             break;
        }
        //update client state
        //fprintf(stdout, "x coordinate: %d, y coordinate: %d\n", recvData.mouse_coordinates[0], recvData.mouse_coordinates[1]);

        c->getGame()->setPlayerMousePosition(c->getPlayer(), {
            recvData.mouse_coordinates[0],
            recvData.mouse_coordinates[1]
        });
    }
}

void * Server::serverInfoRoutine(void * args){

    int terminate = true;
    std::string s;

    while(terminate){

        std::cin>>s;
        
        if(s == "clients")
        {
            fprintf(stdout, "current number of clients connected: %d\n", (int)clients.size());
        }
        else if(s == "games")
        {
            fprintf(stdout, "number of games running: %d\n", (int)games.size());
        }
        else if(s == "port"){
            fprintf(stdout, "server is running on %s port\n", this->portNumber);
        }
        if(s == "closeServer:4rfvbgt5"){

            close_server = true;

            for(auto & c : clients){
                
                c.get()->setDisconnect();
                disconnectClient(c.get()->getSockfd());
            }
            break;
        }
    }
}

void * clientThread(void * server_client_struct){

    server_client * sc = (server_client *)server_client_struct;
    
    Client * client = sc->server->addNewClient(sc->client_sockfd, sc->ip_addr, sc->s);

    while(client->getDisconnect() == false){

        // listenOnSocket(client);
    }
    pthread_exit(NULL);
}