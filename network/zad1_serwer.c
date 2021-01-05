#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 100
#define PORT_NUMBER 1234

struct sockaddr_in baseSa, connectionSa;

socklen_t saSize;

char buf[MAX];


int main(int argv, char* argc[]){
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("Błąd przy tworzeniu uchwytu\n");
        return -1;
    }

    int nFoo = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo)); 
    //przed wywołaniem bind

    baseSa.sin_port = htons(PORT_NUMBER);
    baseSa.sin_addr.s_addr = htonl(INADDR_ANY);

    int foo = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&foo, sizeof(foo))<0){
        printf("Błąd w setsockopt\n");
        return -1;
    }

    if(bind(sockfd, (struct sockaddr *)&baseSa, sizeof(baseSa))<0){
        printf("Błąd w bindowaniu\n");
        return -1;
    }

    if(listen(sockfd, 2) < 0){
        printf("Błąd w ustawianiu nasłuchu na porcie\n");
        return -1;
    }
    
    int sockClient = accept(sockfd, (struct sockaddr *)&connectionSa, &saSize);
    if(sockClient<0){
        printf("Błąd accept\n");
        return -1;
    }
    int a, b;
    read(sockClient, (void *)&a, sizeof(int));
    read(sockClient, (void *)&b, sizeof(int));

    printf("Suma %d + %d = %d\n", a, b, a+b);
    printf("Wysyłam wynik do klienta\n");

    int suma = a + b;

    write(sockClient, (void *)&suma, sizeof(int));

    close(sockClient);
    close(sockfd);

    return 0;
}