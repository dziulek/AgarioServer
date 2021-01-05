#include "server.hpp"

int Server::setUpServer(const std::string portNumber = ""){

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

int Server::addNewClient(int sockfd, const char * ip_addr, struct sockaddr_storage s){

    clients.push_back(std::unique_ptr<Client>(new Client(ip_addr, sockfd, s)));

    fprintf(stdout, "log: new client, ip = %s, socket descriptor = %d\n", ip_addr, sockfd);

    return 0;
}

int Server::disconnectClient(int sockfd){

    fprintf(stdout, "log: disconnecting client, socket = %d\n", sockfd);
    close(sockfd);
}

void Server::createNewGame(){

}

void Server::deleteGame(agario::Game * game){


}

void Server::deleteEmptyGames(){


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

    struct sockaddr_storage client_addr;
    socklen_t str_size = sizeof(client_addr);
    int client_sockfd = accept(this->sockfd, (struct sockaddr *)&client_addr, &str_size);

    if(client_sockfd){

        fprintf(stderr, "accept client: %s\n", gai_strerror(client_sockfd));
        return -1;
    }

    int status = addNewClient(client_sockfd, (char *)get_in_addr((struct sockaddr *)&client_addr), client_addr);
    int status = this->sendDataToClient(clients[0].get());

    disconnectClient(clients[0].get()->getSockfd());
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