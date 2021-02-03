#include "SFMLRenderer.hpp"
#include "engine/game.hpp"
#include "mouseObserver.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "network/server.hpp"


using namespace agario;

int main(){

    srand(time(NULL));

    // Game game;

    // game.addPlayer();

    // SFMLRenderer rend(game);
    // MouseObserver mouse(&rend);

    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // while(rend.getWindow()->isOpen()){

    //     sf::Event event;
    //     while (rend.getWindow()->pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             rend.getWindow()->close();
    //     }

    //     mouse.update(&game.getPlayer(0));

    //     rend.getWindow()->clear();

    //     std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    //     int delta = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    //     begin = std::chrono::steady_clock::now();
    //     game.mainLoop(delta * 1e-6);

    //     rend.drawMap();

    //     std::pair<glm::vec2, glm::vec2> v = game.getPlayer(0).getView();

    //     rend.getView()->setCenter(sf::Vector2f(v.first.x / 2.0 + v.second.x / 2.0, v.second.y / 2.0 + v.first.y / 2.0));
    //     rend.getView()->setSize(sf::Vector2f(
    //         v.second.x - v.first.x,
    //         v.second.y - v.first.y
    //     ));

    //     rend.getWindow()->display();

    //     // rend.getWindow()->setFramerateLimit(60);
    // }


    Server server;

    server.mainLogic();  

    // SendDataFormat data;

    // data.appendString("nickname:dziulek:");

    // std::string siemano = data.getWord(10);

    // std::cout << siemano << std::endl;  

    return 0;
}