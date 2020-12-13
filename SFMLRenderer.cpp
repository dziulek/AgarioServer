#include "SFMLRenderer.hpp"
#include <cmath>
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
        
        drawBomb(**itb);
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

void SFMLRenderer::drawBomb(Bomb & bomb){

    this->window->setView(*this->view);

    int idents = bomb.getNOfIdents();

    sf::VertexArray vertices(sf::TriangleFan, idents * 2 + 2);

    vertices[0] = sf::Vertex(sf::Vector2f(bomb.getPosition().x, bomb.getPosition().y));

    float phi = 2 * PI / float(idents);
    float currAngle = 0;
    float radius = bomb.getRadius();
    float xCoord, yCoord;

    for(int i = 1; i <  vertices.getVertexCount(); i += 2){
        
        xCoord = cos(currAngle) * radius;
        yCoord = sin(currAngle) * radius;
        vertices[i] = sf::Vertex(sf::Vector2f(xCoord, yCoord));
        currAngle += phi;
    }

    currAngle = phi / 2;
    radius *= 0.9;
    for(int i = 2; i < vertices.getVertexCount(); i +=2){

        xCoord = cos(currAngle) * radius;
        yCoord = sin(currAngle) * radius;
        vertices[i] = sf::Vertex(sf::Vector2f(xCoord, yCoord));
        currAngle += phi;
    }

    for(int i = 0; i < vertices.getVertexCount(); i++){
        vertices[i].color = sf::Color(0,255, 0, 255);
    }

    this->window->draw(vertices);
}

void SFMLRenderer::drawMap(ClassicMap & classicMap){

}

void SFMLRenderer::keyCallback(sf::Event event){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

        if(this->view->getSize().x < 1.2 * game->getMap().width)
            this->view->zoom(1.1);
            
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        
        if(this->view->getSize().x > game->getMap().cellWidth * 10)
        this->view->zoom(0.9);
        
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

        float newRatio = float(event.size.height) / float(event.size.width);

        this->view->setSize(sf::Vector2f(viewSize.x, viewSize.x * newRatio));
        this->view->setCenter(center);

    }
}

}