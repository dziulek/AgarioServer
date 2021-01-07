#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

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
#include <string>
#include <iostream>

#define MAX 100

char buf[MAX];

bool stop_sending_data = false;

pthread_mutex_t stop_sending_data_mutex = PTHREAD_MUTEX_INITIALIZER;

struct sendDataFormat{

    char state;
    bool w_action;
    bool divide_action;
    int mouse_coordinates[2];
};

struct sockaddr_in sa;

void * send_data(void * args){

    long server_sockfd = (long)args;

    sendDataFormat sendData;

    bzero(&sendData, sizeof(sendData));

    while(stop_sending_data == false){
        sf::Vector2i mouse_position = sf::Mouse::getPosition();

        //state

        //w_action

        //divide_action

        //mouse coordinates
        sendData.mouse_coordinates[0] = mouse_position.x;
        sendData.mouse_coordinates[1] = mouse_position.y;

        // write(server_sockfd, &sendData, sizeof(sendData));
    }
}

int main(int argc, char ** argv){

    if(argc < 3){
        printf("zad1_klient <ip_address> <port_number>\n");
    }
    else{
        //printf("%s\n", argv[1]);
        //printf("%s\n", argv[2]);
        memset(&sa, 0, sizeof(sa));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(atoi(argv[2]));

        if(inet_pton(AF_INET, argv[1] , &(sa.sin_addr))<=0){
            printf("Błąd przy podawaniu adresu\n");
            return -1;
        }

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == 0){
            printf("Błąd tworzenia uchwytu\n");
            return -1;
        }

        if(connect(sockfd, (struct sockaddr *)&sa, sizeof(sa))<0){
            printf("Błąd łączenia z serwerem\n");
            return -1;
        }

        pthread_t main_thread;

        int status = pthread_create(&main_thread, NULL, send_data, (void *)sockfd);

        std::cout<< "after creating thread\n";
        std::string s;
        while(1){

            std::cin>>s;
            if(s == "siemano"){
                fprintf(stdout, "simeano\n");
            }
            if(s == "close"){

                pthread_mutex_lock(&stop_sending_data_mutex);
                    stop_sending_data = true;
                pthread_mutex_unlock(&stop_sending_data_mutex);
                break;
            }
        }
        std::cout<<"waiting for thread"<< std::endl;
        pthread_join(main_thread, NULL);

        close(sockfd);
    }

    return 0;
}