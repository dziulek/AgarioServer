#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "../sendDataFormat.hpp"

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
#include <cmath>

#define MAX 100

char buf[MAX];

#define WAIT 0
#define PLAY 1
#define START_SHAPES 50

struct game_state{

    float state;
    float window_width;
    float window_height;
}current_game_state;

int player_state = WAIT;

bool stop_sending_data = false;

pthread_mutex_t stop_sending_data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t game_state_mutex = PTHREAD_MUTEX_INITIALIZER;

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
        // sf::Vector2i mouse_position = sf::Mouse::getPosition();

        //state

        //w_action

        //divide_action

        //mouse coordinates
        // sendData.mouse_coordinates[0] = mouse_position.x;
        // sendData.mouse_coordinates[1] = mouse_position.y;

        // write(server_sockfd, &sendData, sizeof(sendData));

        char buf[1];
        buf[0] = 'p';
        int status = write(server_sockfd, buf, 1);

        if(status == -1){
            fprintf(stderr, "sending data to server: %s\n", gai_strerror(errno));
            pthread_exit(NULL);
        }
    }
}

void interpretData(char * data, int size){

    pthread_mutex_lock(&game_state_mutex);

    current_game_state.state = data[0];
    // current_game_state.window_width = data[1];
    // current_game_state.window_height = data[2];

    pthread_mutex_unlock(&game_state_mutex);
}

void * handleConnection(void * args){

    long server_sockfd = (long)args;

    pthread_t send_thread;
    int status = pthread_create(&send_thread, NULL, send_data, (void *)server_sockfd);

    if(status){

        fprintf(stderr, "create send data thread: %s\n", gai_strerror(errno));
        pthread_exit(NULL);
    }

    SendDataFormat data;

    while(stop_sending_data == false){
        
        data.clearBuf();
        int status = read(server_sockfd, data.getBuf(), MAX_LEN_BUFER);

        if(status == 0){

            //socket closed
            fprintf(stdout, "server socket closed\n");
            break;
        }
        if(status == -1){

            fprintf(stdout, "cannot read data\n");
            break;
        }
        data.printBuf();

    }

    pthread_join(send_thread, NULL);
}

void drawStartScreen(sf::RenderWindow & window, sf::View & view, sf::Text & text){

    window.setView(view);

    text.setPosition(sf::Vector2f(view.getSize().x/2.0f, view.getSize().y/2.0f));
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);

    window.draw(text);
}

void drawMesh(sf::RenderWindow & window, sf::View & view){

    window.setView(view);

    float xsize = view.getSize().x;
    float ysize = view.getSize().y;

    float xmin = view.getCenter().x - 5 - xsize / 2;
    float xmax = view.getCenter().x + 5 + xsize / 2;
    float ymin = view.getCenter().y - 5 - ysize / 2;
    float ymax = view.getCenter().y + 5 + ysize / 2;

    sf::Vertex vertical_line[2] = {
        sf::Vertex(sf::Vector2f(xmin, ymin)),
        sf::Vertex(sf::Vector2f(xmin, ymax))
    };

    for(float i = floor(xmin/10) * 10; i < xmax; i+=10.0f){

        window.draw(vertical_line, 2, sf::Lines);
        
        vertical_line[0].position.x += 10;
        vertical_line[1].position.x += 10;
    }

    sf::Vertex horizontal_line[2] = {
        sf::Vertex(sf::Vector2f(xmin, ymin)),
        sf::Vertex(sf::Vector2f(xmax, ymin))
    };

    for(float i = floor(ymin/10) * 10; i < ymax; i+=10){

        window.draw(horizontal_line, 2, sf::Lines);

        horizontal_line[0].position.y += 10;
        horizontal_line[1].position.y += 10;
    }
}

void drawGameView(sf::RenderWindow & window, sf::View view){

    pthread_mutex_lock(&game_state_mutex);

    // std::cout<<"map width: "<<current_game_state.window_width<<std::endl;
    // std::cout<<"map height: "<<current_game_state.window_height<<std::endl;

    pthread_mutex_unlock(&game_state_mutex);
}


int main(int argc, char ** argv){

    srand(time(NULL));

    if(argc < 3){
        printf("zad1_klient <ip_address> <port_number>\n");
    }
    else{

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

        int status = pthread_create(&main_thread, NULL, handleConnection, (void *)sockfd);

        sf::RenderWindow window(sf::VideoMode(900, 600), "Agario!");
        sf::View main_view;
        main_view.setSize(window.getSize().x, window.getSize().y);
        main_view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        main_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

        window.setView(main_view);

        sf::Font font;
        if(!font.loadFromFile("eastman/EastmanTrial-Black.otf")){
            fprintf(stderr, "could not load font\n");
            return -1;
        }

        sf::Text text;
        text.setFont(font);

        text.setString("click SPACE to play");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Blue);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::Resized){//fix need

                    sf::Vector2f center = main_view.getCenter();

                    sf::Vector2f viewSize = main_view.getSize();

                    sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());

                    float x_per = float(event.size.width)/windowSize.x;
                    float y_per = float(event.size.height)/windowSize.y;

                    float newRatio = float(event.size.height) / float(event.size.width);

                    main_view.setSize(viewSize.x, viewSize.x * newRatio);
                    main_view.setCenter(center);
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

                    player_state = PLAY;
                }
            }

            window.clear();

            if(player_state == WAIT){

                drawStartScreen(window, main_view, text);
            }
            else if(player_state == PLAY){

                drawMesh(window, main_view);
                drawGameView(window, main_view);
            }


            window.display();
        }

        std::string s;
        while(1){

            std::cin>>s;
            if(s == "siemano"){
                fprintf(stdout, "siemano\n");
            }
            if(s == "close"){

                pthread_mutex_lock(&stop_sending_data_mutex);
                    stop_sending_data = true;
                pthread_mutex_unlock(&stop_sending_data_mutex);
                break;
            }
        }

        pthread_join(main_thread, NULL);

        close(sockfd);
    }

    return 0;
}