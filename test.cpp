#include "SFMLRenderer.hpp"
#include "engine/game.hpp"
#include "mouseObserver.hpp"
#include "engine/maps/mapMiniController.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>


using namespace agario;

class C{

public:

    float xd;

    C(float x) : xd(x){}
};

class A{


    public:

    std::vector<std::unique_ptr<C>> cc;
    int  a;
    int b;

    A(int a, int b){
        this->a = a;
        this->b = b;

        cc.push_back(std::unique_ptr<C>(new C(3.0)));
    }
};

class B : public A{

public:

    int c;

    B(int a, int b, int c) : A(a,b){
        this->c = c;
    }
};


int main(){
    srand(time(NULL));

    Game game;
    game.addPlayer();
    
    // std::unique_ptr<B> pointer = std::make_unique<B>(4,5,6);
    // std::vector<std::unique_ptr<B>> vec;
    // vec.push_back(std::move(pointer));

    SFMLRenderer rend(game);
    MouseObserver mo(&rend);
    MapMiniController cont(game.getMap());
    

    while(rend.getWindow()->isOpen()){

        sf::Event event;
        while(rend.getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                rend.getWindow()->close();
            }
        }
        rend.getWindow()->clear();
        
        cont.update();
        rend.drawMap();
        mo.update(&rend.getGame()->getPlayer(0));
        game.mainLoop(1.0f/30);


        rend.getWindow()->display();
        rend.getWindow()->setFramerateLimit(60);
    
    }

    return 0;
}