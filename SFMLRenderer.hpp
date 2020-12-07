#ifndef SFML_RENDERER_HPP
#define SFML_RENDERER_HPP

#include "renderer.hpp"
#include "gameObject.hpp"
#include "map.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace agario{

class SFMLRenderer : Renderer{

private:

    sf::RenderWindow * window;
    sf::View * view;



public:

    SFMLRenderer(){
        
        window = new sf::RenderWindow();
        view = new sf::View();
    }
    void drawGameObject(const GameObject & gameObject) override;
    void drawMap(const Map & map);

};


}

#endif