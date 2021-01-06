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

struct sockaddr_in sa;

void * send_data(void * args){

    long server_sockfd = (long)args;

    while(1){

        sf::Vector2i mouse_position = sf::Mouse::getPosition();

        write(server_sockfd, &mouse_position, 8);
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

        std::string s;
        while(true){

            std::cin>>s;
            if(s == "close"){
                std::cout<<"close soon"<<std::endl;
                pthread_exit(&main_thread);
                break;
            }
        }

        pthread_join(main_thread, NULL);

        close(sockfd);
    }

    return 0;
}