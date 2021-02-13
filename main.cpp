#include "engine/game.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "network/server.hpp"

#include "renderers/SFMLRenderer.hpp"
#include "renderers/mouseObserver.hpp"


using namespace agario;

int main(){

    srand(time(NULL));

    Game game;

    game.addPlayer();

    game.getPlayer(0).setColor();

    SFMLRenderer rend(game);
    MouseObserver mouse(&rend);

    while(rend.getWindow()->isOpen()){

        sf::Event event;
        while (rend.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rend.getWindow()->close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                game.wAction(&game.getPlayer(0));
            }
        }

        mouse.update(&game.getPlayer(0));

        rend.getWindow()->clear();

        game.mainLoop(1.0f / 30);

        rend.drawMap();

        std::pair<glm::vec2, glm::vec2> v = game.getPlayer(0).getView();

        rend.getView()->setCenter(sf::Vector2f(v.first.x / 2.0 + v.second.x / 2.0, v.second.y / 2.0 + v.first.y / 2.0));
        rend.getView()->setSize(sf::Vector2f(
            v.second.x - v.first.x,
            v.second.y - v.first.y
        ));

        rend.getWindow()->display();

        rend.getWindow()->setFramerateLimit(60);
    }

    // Server server;

    // server.mainLogic();   

    return 0;
}