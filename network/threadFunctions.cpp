#include "threadFunctions.hpp"

void * clientThread(void * server_client_struct){

    server_client * sc = (server_client *)server_client_struct;
    
    Client * client = sc->server->addNewClient(sc->client_sockfd, sc->ip_addr, sc->s);

    DataFormatServer buf;
    clientInfo cinfo;

    while(client != nullptr && client->getDisconnect() == false){

        buf.clearBuf();

        int status = recv(client->getSockfd(), buf.getBuf(), 150, 0);
        if(status == 0){
            //closed socket
            break;
        }


        if(strcmp("get:game", buf.getBuf()) == 0){

            buf.clearBuf();
            if(client->getPlayer() == nullptr || client->getPlayer()->getSize() == 0){
                
                client->getPlayer()->setState(false);
                std::cout << "xd" << std::endl;
            }

            int status = sc->server->sendDataToClient(client);

            if(status == -1){
                fprintf(stdout, "client disconnected: %s\n", client->getIp_addr());
            }

        }
        else if(strcmp("get:score", buf.getBuf()) == 0){

        }
        else if(buf.getWord(0) == "nickname"){

            int ind = buf.getNextIndexSeparator(0);
            std::string nick = buf.getWord(ind);

            client->getPlayer()->setNickname(nick);
            client->getPlayer()->setColor();

            int status = send(client->getSockfd(), "conf", 4, 0);

            if(status == -1){
                fprintf(stdout, "client disconnected: %s\n", client->getIp_addr());
            }
        }
        else if(buf.getBuf()[0] == ':'){
            // buf.printBuf();
            buf.extractClientInfo(cinfo);
            client->getGame()->setPlayerMousePosition(client->getPlayer(), cinfo.mousePosition);
        }
        
    }

    pthread_mutex_lock(&sc->server->client_creation_mutex);

    pthread_mutex_lock(&sc->server->new_player_mutex);

    client->setDisconnect();
    client->getGame()->deletePlayer(client->getPlayer());

    pthread_mutex_unlock(&sc->server->new_player_mutex);
    sc->server->cullDisconnectedClients();

    pthread_mutex_unlock(&sc->server->client_creation_mutex);

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
