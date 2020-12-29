#include "SFMLRenderer.hpp"
#include "game.hpp"
#include <vector>
#include <iostream>

using namespace agario;

int main(){
    std::cout<<"ale";
    Game game;
    game.addPlayer();
    

    SFMLRenderer rend(game);
    

    while(rend.getWindow()->isOpen()){

        sf::Event event;
        while(rend.getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                rend.getWindow()->close();
            }
        }

        rend.drawMap();


        rend.getWindow()->display();
        rend.getWindow()->setFramerateLimit(60);
    
    }

    return 0;
}