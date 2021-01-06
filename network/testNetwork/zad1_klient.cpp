#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 100

char buf[MAX];

struct sockaddr_in sa;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;

void * client_listen(void * server_sockfd){

    long server = (long)server_sockfd;

    while(1){

        bzero(buf, MAX);
        pthread_mutex_lock(&buf_mutex);
        int fun = read(server, buf, MAX);
        pthread_mutex_unlock(&buf_mutex);


        if(fun == -1){

            fprintf(stderr, "reading in listener: %s\n", gai_strerror(fun));
            exit(-1);
        }
        fprintf(stdout, "%s", buf);

    }

    pthread_exit(NULL);
}



void * start_routine(void * server_sockfd){

    long sockfd = (long)server_sockfd;

    pthread_t listener;

    int status = pthread_create(&listener, NULL, client_listen, server_sockfd);

    if(status){

        fprintf(stderr, "creating listener: %s\n", gai_strerror(status));
        exit(-1);
    }

    char local_buf[MAX];

    while(strcmp(local_buf, "close_connection") != 0){
        
        bzero(local_buf, MAX);
        scanf("%s", local_buf);

        pthread_mutex_lock(&buf_mutex);
        write(sockfd, local_buf, MAX);
        pthread_mutex_unlock(&buf_mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){//arguments: ip address, port number

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

        int status = pthread_create(&main_thread, NULL, start_routine, (void *)sockfd);

        pthread_join(main_thread, NULL);

        close(sockfd);
    }
    return 0;
}

