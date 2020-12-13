#include "./maps/map.hpp"
#include "SFMLRenderer.hpp"
#include "game.hpp"
#include <vector>
#include <iostream>

using namespace agario;

int main(){
    
    Game game;

    GameObject gameObject;
    game.getMap().addGameObject(gameObject);

    SFMLRenderer rend(game);
    

    while(rend.getWindow()->isOpen()){

        sf::Event event;
        while(rend.getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                rend.getWindow()->close();
            }

            rend.keyCallback(event);
        }


        rend.getWindow()->clear();
        rend.drawMap(game.getMap());

        rend.getWindow()->display();
        rend.getWindow()->setFramerateLimit(60);
    
    }



    return 0;
}