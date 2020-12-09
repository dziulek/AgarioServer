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

#define PORT_NUMBER "1234"

unsigned int currNumberOfClients = 0;

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int main(int argc, char *argv[]){

    int status;
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *serverInfo;
    int opt_value = 1;
    char s[INET_ADDRSTRLEN];


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(NULL, PORT_NUMBER, &hints, &serverInfo)) != 0){
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

    while(1){

        struct sockaddr_storage *  clientAddr = new sockaddr_storage;
        socklen_t addrSize = sizeof(*clientAddr); 

        int client_sockfd = accept(sockfd, (struct sockaddr *)clientAddr, &addrSize);
        if(status == -1){
            fprintf(stderr, "accept error: %s\n", gai_strerror(client_sockfd));
            return -1;
        }

        inet_ntop(clientAddr->ss_family, get_in_addr((struct sockaddr *)clientAddr), s, sizeof(s));
        fprintf(stdout, "got connection from %s\n", s);
        close(client_sockfd);
    }

    return 0;
}