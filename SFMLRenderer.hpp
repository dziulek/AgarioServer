#ifndef SFML_RENDERER_HPP
#define SFML_RENDERER_HPP

#include "renderer.hpp"
#include "./maps/testMap.hpp"
#include "./maps/classicMap.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace agario{

class SFMLRenderer : Renderer{

private:

    sf::RenderWindow * window;
    sf::View * view;

    Game * game;
    
public:

    SFMLRenderer(Game & g){
        
        game = &g;
        window = new sf::RenderWindow(sf::VideoMode(1000, 500), "Agario");
        view = new sf::View();
        view->setSize(sf::Vector2f(1.2 * game->getMap().width, 1.2 * game->getMap().height));
        view->setCenter(sf::Vector2f(game->getMap().width/2.0f, game->getMap().height/2.0f));
        view->setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
        
    }

    ~SFMLRenderer(){
        delete window;
        delete view;
    }
    
    sf::RenderWindow * getWindow(){ return this->window;}
    sf::View * getView(){ return this->view;}

    void drawMap(TestMap & map) override;
    void drawMap(ClassicMap & map) override;
    void drawGameObject(GameObject & gameObject);
    void drawBomb(Bomb & bomb);
    void keyCallback(sf::Event event);

};


}

#endif