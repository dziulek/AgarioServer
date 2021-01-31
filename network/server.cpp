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
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

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

    pthread_mutex_lock(&client_creation_mutex);

    std::unique_ptr<Client> new_client = std::unique_ptr<Client>(new Client(ip_addr, sockfd, s));
    clients.push_back(std::move(new_client));
    findGameForNewClient(clients.back().get());

    pthread_mutex_unlock(&client_creation_mutex);

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

    for(auto & c : clients){

        if(c.get() != nullptr && c.get()->getDisconnect() == false){
            
            int status = sendDataToClient(c.get());

            if(status == -1){
                fprintf(stdout, "client disconnected: %s\n", c->getIp_addr());
            }
        }
    }
}

void * Server::sendDataThread(void * args){

    while(close_server == false){
        
        sleep(5);
        pthread_mutex_lock(&client_creation_mutex);

        sendDataToClients(NULL);

        pthread_mutex_unlock(&client_creation_mutex);
    }


    fprintf(stdout, "exit from send data thread\n");
    pthread_exit(NULL);
}

void Server::fillDataToClient(Client * client, DataFormatServer & data){

    data.clearBuf();

    // data.appendMinis(client->getGame(), client->getPlayer());
    //player coordinates
    for(int i = 0; i < client->getGame()->getnOfPlayers(); i ++){

        data.appendPlayer(&client->getGame()->getPlayer(i));     
    }
    data.appendChar(PLAYER);

    data.appendView(client->getPlayer());

    //bomb coordinates
}

int Server::sendDataToClient(Client * client){

    DataFormatServer data;
    fillDataToClient(client, data);

    int status = write(client->getSockfd(), (void *)data.getBuf(), data.getLen());

    if(status == -1){

        fprintf(stdout, "cannot send data to client under %s, error: %s\n", client->getIp_addr(), gai_strerror(errno));
        client->setDisconnect();
        return -1;
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
    
    status = pthread_create(&this->game_thread, NULL, gameThread, (void *)this);

    if(status){

        fprintf(stderr, "creating game thread: %s", gai_strerror(status));
    }

    struct sockaddr_storage client_addr;
    socklen_t str_size = sizeof(client_addr);

    while(close_server == false){

        int client_sockfd = accept(this->sockfd, (struct sockaddr *)&client_addr, &str_size);
        if(client_sockfd == -1){

            if(errno == EAGAIN || errno == EWOULDBLOCK){
                continue;
            }
            else {

                fprintf(stderr, "accept client: %s\n", gai_strerror(client_sockfd));
                return -1;
            }

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
    pthread_join(this->game_thread, NULL);

    for(auto & c : clients){

        pthread_join(c.get()->getThreadId(), NULL);
    }
    fprintf(stdout, "exit from main thread\n");

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
            
            pthread_mutex_lock(&new_player_mutex);
            agario::Player * p = g.get()->addPlayer();
            client->setPlayer(p);
            client->setGame(g.get());
            pthread_mutex_unlock(&new_player_mutex);
            added = true;
            break;
        }
        
    }

    if(added == false){


        pthread_mutex_lock(&new_player_mutex);
        this->createNewGame();
 
        agario::Player * p = games.back().get()->addPlayer();
        client->setPlayer(p);
        client->setGame(games.back().get());
        pthread_mutex_unlock(&new_player_mutex);

    }
}

void Server::interpretData(recvDataFormat * data){


}

int  Server::listenOnSocket(Client * client){

        DataFormatServer data_in;

        int n = read((long)client->getSockfd(), data_in.getBuf(), MAX_LEN_BUFER);

        if(n == 0){
            //closed socket
            client->setDisconnect();

            return 0;
        }
        //update client state
        clientInfo cinfo;
        data_in.extractClientInfo(cinfo);

        std::cout<<cinfo.mousePosition.x<< " " << cinfo.mousePosition.y<<std::endl;
        //mouse position
        client->getGame()->setPlayerMousePosition(client->getPlayer(), cinfo.mousePosition);
        //divide action

        //w action


        return n;
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
        else if(s == "cullClients"){

            cullDisconnectedClients();
            fprintf(stdout, "deleting disconnected clients\n");
        }
        else if(s == "time"){
            
            std::time_t time = this->getServerTime();

            std::cout<<std::ctime(&time)<<std::endl;
        }
        if(s == "closeServer:4rfvbgt5"){

            this->close_server = true;

            for(auto & c : clients){
                
                c.get()->setDisconnect();
                disconnectClient(c.get()->getSockfd());
            }
            break;
        }
    }

    fprintf(stdout, "exit from infoServerRoutine thread\n");
    pthread_exit(NULL);
}

void Server::sig_pipe_signal_handler(int signum){

    fprintf(stdout, "client disconnected\n");
}

void Server::non_blocking_socket_signal(int signum){
    
}

void Server::cullDisconnectedClients(){

    std::vector<std::unique_ptr<Client>>::iterator it;
    for(it = clients.begin(); it != clients.end(); it++){

        if(it->get()->getDisconnect() == true){

            it->reset();
            *it = std::move(clients.back());
            clients.pop_back();
            it--;
        }
    }
}

void Server::gameLoop(const float dTime){

    for(auto & g : games){

        if(g.get() != nullptr)
            pthread_mutex_lock(&new_player_mutex);
            g.get()->mainLoop(dTime); 
            pthread_mutex_unlock(&new_player_mutex);
    }
}

const std::time_t Server::getServerTime(){

    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}