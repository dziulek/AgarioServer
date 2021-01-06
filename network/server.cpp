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

int Server::addNewClient(int sockfd, char * ip_addr, struct sockaddr_storage * s){

    clients.push_back(std::unique_ptr<Client>(new Client(ip_addr, sockfd, s)));

    fprintf(stdout, "log: new client, ip = %s, socket descriptor = %d\n", ip_addr, sockfd);

    return 0;
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

void Server::sendDataToClients(){

    for(auto & c : clients){

        int status = sendDataToClient(c.get());

        if(status < 0){

        }
    }
}

int Server::sendDataToClient(Client * client){

    write(client->getSockfd(), "test", 10);
}

int Server::mainLogic(){

    int status = pthread_create(&this->server_thread, NULL,  (THREADFUNCPTR) &Server::serverInfoRoutine, this);

    if(status){

        fprintf(stderr, "creating server thread: %s", gai_strerror(status));
        return -1;
    }

    struct sockaddr_storage client_addr;
    socklen_t str_size = sizeof(client_addr);
    int client_sockfd = accept(this->sockfd, (struct sockaddr *)&client_addr, &str_size);

    if(client_sockfd == -1){

        fprintf(stderr, "accept client: %s\n", gai_strerror(client_sockfd));
        return -1;
    }
    char s[INET_ADDRSTRLEN];
    inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)&client_addr), s, sizeof(s));
    status = addNewClient(client_sockfd, s, &client_addr);

    while(1){

        listenOnSocket((void *)client_sockfd);
    }

    pthread_join(this->server_thread, NULL);
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

            g.get()->addPlayer();
            added = true;
            break;
        }
        
    }

    if(added = false){

        this->createNewGame();

        games.back().get()->addPlayer();
    }
}

void Server::interpretData(void * data){


}

void * Server::listenOnSocket(void * client_socketfd){

    bool client_is_there = 1;

    struct recvDataFormat recvData;

    while(client_is_there){

        int n = read((long)client_socketfd, (void *)&recvData, 8);

        //update client state
        fprintf(stdout, "x coordinate: %d, y coordinate: %d\n", recvData.mouse_coordinates[0], recvData.mouse_coordinates[1]);
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
        if(s == "closeServer:4rfvbgt5"){

            for(auto & c : clients){
                
                pthread_exit(&c.get()->getThreadId());
                close(c.get()->getSockfd());
            }
            break;
        }
    }
}