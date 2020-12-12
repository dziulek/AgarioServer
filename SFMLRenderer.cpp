#include "SFMLRenderer.hpp"
#include <iostream>


namespace agario{

using namespace agario::shapes;

void SFMLRenderer::drawGameObject(GameObject & gameObject){

    sf::CircleShape sparkle;

    for(int i = 0; i < gameObject.getSparklesSize(); i++){

        sparkle.setRadius(gameObject[i].getRadius());
        sparkle.setPosition(gameObject[i].getPosition().x, gameObject[i].getPosition().y);
        this->window->draw(sparkle);
    }
}

void SFMLRenderer::drawMap(TestMap & map){

    this->window->setView(*this->view);

    //draw background

    //draw lines
    float x = 0.0f, y = 0.0f;

    sf::Transform transformX, transformY;
    transformX.translate(sf::Vector2f(x, 0.0f));
    transformY.translate(sf::Vector2f(0.0f, y));

    sf::Vertex horLine[] ={
        sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
        sf::Vertex(sf::Vector2f(map.width, 0.0f))
    };

    horLine[0].color = sf::Color(50, 50, 50, 255);
    horLine[1].color = sf::Color(50, 50, 50, 255);

    while(y <= map.height + 1){
        this->window->draw(horLine, 2, sf::Lines, transformY);

        y += map.cellWidth;
        transformY.translate(sf::Vector2f(0.0f, map.cellWidth));
    }

    sf::Vertex verLine[] = {
        sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
        sf::Vertex(sf::Vector2f(0.0f, map.height))
    };

    verLine[0].color = sf::Color(50, 50, 50, 255);
    verLine[1].color = sf::Color(50, 50, 50, 255);

    while(x <= map.width + 1){
        this->window->draw(verLine, 2, sf::Lines, transformX);
        x += map.cellWidth;
        transformX.translate(sf::Vector2f(map.cellWidth, 0.0f));
    }

    //draw bombs
    std::vector<Bomb *>::iterator itb = map.getBombIterator().begin();

    for(itb; itb != map.getBombIterator().end(); itb++){

    }
    //draw minis
    std::vector<const Mini *>::iterator itm = map.getMiniIterator().begin();

    for(itm; itm != map.getMiniIterator().end(); itm++){

    }
    //draw gameObjects
    std::vector<GameObject *>::iterator itg = map.getGameObjIterator().begin();

    for(itg; itg != map.getGameObjIterator().end(); itg++){
        
        drawGameObject(**itg);
    }

}

void SFMLRenderer::drawMap(ClassicMap & classicMap){

}

void SFMLRenderer::keyCallback(sf::Event event){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

        if(this->view->getSize().x < 1.2 * game->getMap().width)
            this->view->zoom(1.1);
        //std::cout<<this->view->getSize().x<<" "<< this->view->getSize().y<<std::endl;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        
        if(this->view->getSize().x > game->getMap().cellWidth * 10)
        this->view->zoom(0.9);
        
        //std::cout<<this->view->getSize().x<<" "<< this->view->getSize().y<<std::endl;

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

        if(this->view->getCenter().y > 0)
            this->view->move(sf::Vector2f(0,-10));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

        if(this->view->getCenter().y < game->getMap().height)
            this->view->move(sf::Vector2f(0,10));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

        if(this->view->getCenter().x < game->getMap().width)
            this->view->move(sf::Vector2f(10,0));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

        if(this->view->getCenter().x > 0)
            this->view->move(sf::Vector2f(-10,0));
    }
    else if(event.type == sf::Event::Resized){

        sf::Vector2f center = this->view->getCenter();

        sf::Vector2f viewSize = this->view->getSize();

        sf::Vector2f windowSize = static_cast<sf::Vector2f>(this->window->getSize());

        float x_per = float(event.size.width)/windowSize.x;
        float y_per = float(event.size.height)/windowSize.y;

        this->view->setSize(sf::Vector2f(viewSize.x * x_per, viewSize.y * y_per));
        this->view->setCenter(center);

    }
}

}