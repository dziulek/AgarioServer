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
#include <vector>

#define PORT_NUMBER "1234"

unsigned int currNumberOfClients = 0;

#define MAX 100

struct shared_data{

    std::vector<int> sock_clients; 
    char message[MAX];
};

shared_data data;

pthread_mutex_t message_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t listener_writer_mutex = PTHREAD_COND_INITIALIZER;

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void * testFunction(void * argsxd){

    long client = (long)argsxd;

    char local_copy[MAX];
    
    while(1){

        pthread_mutex_lock(&message_mutex);
        int fun = read(client, local_copy, MAX);
        pthread_mutex_unlock(&message_mutex);
        if(fun == -1){

            fprintf(stderr, "reading from client: %s\n", gai_strerror(fun));
            exit(-1);
        }
        if(fun == 0){

            fprintf(stdout, "client breaks the connection\n");
            break;
        }
        fprintf(stdout, "%s\n", local_copy);
    }

    pthread_exit(NULL);
}

void * handleClient(void * clientSockfd){

    long client_sockfd = (long)clientSockfd;

    pthread_t listener;

    int listener_id = pthread_create(&listener, NULL, testFunction, clientSockfd);

    if(listener_id){

        fprintf(stderr, "creating a new thread: %s\n", gai_strerror(listener_id));
    }

    char local_buf[MAX];

    while(strcmp(local_buf, "close_connection")){
        
        bzero(local_buf, MAX);
        scanf("%s", local_buf);

        pthread_mutex_lock(&message_mutex);
        int fun = write(client_sockfd, local_buf, MAX);
        pthread_mutex_unlock(&message_mutex);

        if(fun == -1){

            fprintf(stderr, "write to client: %s\n", gai_strerror(fun));
            exit(-1);
        }
    }
    fprintf(stdout, "client disconnected: %d\n", (int)client_sockfd);

    pthread_exit(&listener);
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

    std::vector<int> threads;

        struct sockaddr_storage *  clientAddr = new sockaddr_storage;
        socklen_t addrSize = sizeof(*clientAddr); 

        int client_sockfd = accept(sockfd, (struct sockaddr *)clientAddr, &addrSize);
        if(status == -1){
            fprintf(stderr, "accept error: %s\n", gai_strerror(client_sockfd));
            return -1;
        }

        inet_ntop(clientAddr->ss_family, get_in_addr((struct sockaddr *)clientAddr), s, sizeof(s));
        fprintf(stdout, "log server: got connection from %s\n", s);

        data.sock_clients.push_back(client_sockfd);

        pthread_t clientThread;
        int pthread_id = pthread_create(&clientThread, NULL, handleClient, (void *)client_sockfd);

        if(pthread_id){
            fprintf(stderr, "creating new thread: %s\n", gai_strerror(pthread_id));
            return -1;
        }

        threads.push_back(pthread_id);

    pthread_join(clientThread, NULL);

    close(sockfd);

    return 0;
}