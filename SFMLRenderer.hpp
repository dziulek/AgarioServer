#ifndef SFML_RENDERER_HPP
#define SFML_RENDERER_HPP

#include "renderer.hpp"
#include "gameObject.hpp"
#include "testMap.hpp"
#include "classicMap.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace agario{

class SFMLRenderer : Renderer{

private:

    sf::RenderWindow * window;
    sf::View * view;

    void drawGameObject(GameObject & gameObject);
    
public:

    SFMLRenderer(){
        
        window = new sf::RenderWindow();
        view = new sf::View();
    }

    ~SFMLRenderer(){
        delete window;
        delete view;
    }
    
    void drawMap(TestMap & map) override;
    void drawMap(ClassicMap & map) override;

};


}

#endif