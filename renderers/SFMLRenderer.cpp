#include "SFMLRenderer.hpp"
#include <cmath>
#include <iostream>


namespace agario{

using namespace agario::shapes;

void SFMLRenderer::drawMap(){

    this->window->setView(*view);
    //draw only borders
    sf::VertexArray borders(sf::LineStrip, 5);
    borders[0] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));
    borders[1] = sf::Vertex(sf::Vector2f(0.0f, game->getMap()->height));
    borders[2] = sf::Vertex(sf::Vector2f(game->getMap()->width, game->getMap()->height));
    borders[3] = sf::Vertex(sf::Vector2f(game->getMap()->width, 0.0f));
    borders[4] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));

    window->draw(borders);

    //draw minis
    sf::CircleShape mm(MINI_RADIUS);
    mm.setOrigin(MINI_RADIUS, MINI_RADIUS);
    for(auto & i : game->getMap()->minis){

        for(auto & j : i){

            for(auto & k : j){

                if(k.get() == nullptr){
                    std::cout<<"nie"<<std::endl;
                    continue;
                }
                mm.setPosition({k.get()->getPosition().x, k.get()->getPosition().y});
                mm.setFillColor(sf::Color(k.get()->getColor()));
                window->draw(mm);
            }
        }
    }
    //draw bombs
    for(auto & b : this->game->getMap()->bombs){

        sf::CircleShape octagon(BOMB_RADIUS, 8);
        octagon.setPosition(sf::Vector2f(b.get()->getXCoord(), b.get()->getYCoord()));
        octagon.setFillColor(sf::Color::Green);
        window->draw(octagon);

    }

    //  draw other shapes
    for(auto & shape : this->game->getMap()->abandoned){
        sf::CircleShape w(shape.get()->getRadius());
        w.setFillColor(sf::Color(shape.get()->getColor()));
        w.setOrigin(sf::Vector2f(shape.get()->getRadius(), shape.get()->getRadius()));

        w.setPosition(sf::Vector2f(shape.get()->getPosition().x, shape.get()->getPosition().y));

        window->draw(w);
    }
   
   //draw players
   for(int i = 0; i < this->game->getnOfPlayers(); i++){

       for(int j = 0; j < game->getPlayer(i).getSize(); j++){
           
           float r = game->getPlayer(i)[j].getRadius();
           sf::CircleShape blob(r);
           blob.setFillColor(sf::Color(game->getPlayer(i)[j].getColor()));
           blob.setOrigin(sf::Vector2f(r,r));

           blob.setPosition(sf::Vector2f(game->getPlayer(i)[j].getPosition().x,
                            game->getPlayer(i)[j].getPosition().y));
            window->draw(blob);

            sf::Vector2f pos = sf::Vector2f(game->getPlayer(i)[j].getPosition().x, game->getPlayer(i)[j].getPosition().y);

            sf::Vertex line[2] = {
                sf::Vertex(pos),
                sf::Vertex(pos + sf::Vector2f(game->getPlayer(i)[j].getVelocity().x, game->getPlayer(i)[j].getVelocity().y))
            };

            window->draw(line, 2, sf::Lines);

            // sf::VertexArray line(sf::Lines, 2);
            // line[0] = blob.getPosition();
            // line[1] = 
       }
   }
}

// void SFMLRenderer::drawMap(Map & map){

//     this->window->setView(*this->view);

//     //draw bombs
//     std::vector<Bomb *>::iterator itb = map.getBombIterator().begin();

//     for(itb; itb != map.getBombIterator().end(); itb++){
        
//         drawBomb(**itb);
//     }
//     //draw minis
//     std::vector<const Mini *>::iterator itm = map.getMiniIterator().begin();

//     for(itm; itm != map.getMiniIterator().end(); itm++){

//     }
//     //draw gameObjects
//     std::vector<GameObject *>::iterator itg = map.getGameObjIterator().begin();

//     for(itg; itg != map.getGameObjIterator().end(); itg++){
        
//         drawGameObject(**itg);
//     }

// }

// void SFMLRenderer::drawBomb(Bomb & bomb){

//     this->window->setView(*this->view);

//     int idents = bomb.getNOfIdents();

//     sf::VertexArray vertices(sf::TriangleFan, idents * 2 + 2);

//     vertices[0] = sf::Vertex(sf::Vector2f(bomb.getPosition().x, bomb.getPosition().y));

//     float phi = 2 * PI / float(idents);
//     float currAngle = 0;
//     float radius = bomb.getRadius();
//     float xCoord, yCoord;

//     for(int i = 1; i <  vertices.getVertexCount(); i += 2){
        
//         xCoord = cos(currAngle) * radius;
//         yCoord = sin(currAngle) * radius;
//         vertices[i] = sf::Vertex(sf::Vector2f(xCoord, yCoord));
//         currAngle += phi;
//     }

//     currAngle = phi / 2;
//     radius *= 0.9;
//     for(int i = 2; i < vertices.getVertexCount(); i +=2){

//         xCoord = cos(currAngle) * radius;
//         yCoord = sin(currAngle) * radius;
//         vertices[i] = sf::Vertex(sf::Vector2f(xCoord, yCoord));
//         currAngle += phi;
//     }

//     for(int i = 0; i < vertices.getVertexCount(); i++){
//         vertices[i].color = sf::Color(0,255, 0, 255);
//     }

//     this->window->draw(vertices);
// }

// void SFMLRenderer::drawMap(ClassicMap & classicMap){

// }

// void SFMLRenderer::keyCallback(sf::Event event){

//     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

//         if(this->view->getSize().x < 1.2 * game->getMap().width)
//             this->view->zoom(1.1);
            
//     }
//     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        
//         if(this->view->getSize().x > game->getMap().cellWidth * 10)
//         this->view->zoom(0.9);
        
//     }
//     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

//         if(this->view->getCenter().y > 0)
//             this->view->move(sf::Vector2f(0,-10));
//     }
//     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

//         if(this->view->getCenter().y < game->getMap().height)
//             this->view->move(sf::Vector2f(0,10));
//     }
//     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

//         if(this->view->getCenter().x < game->getMap().width)
//             this->view->move(sf::Vector2f(10,0));
//     }
//     else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

//         if(this->view->getCenter().x > 0)
//             this->view->move(sf::Vector2f(-10,0));
//     }
//     else if(event.type == sf::Event::Resized){

//         sf::Vector2f center = this->view->getCenter();

//         sf::Vector2f viewSize = this->view->getSize();

//         sf::Vector2f windowSize = static_cast<sf::Vector2f>(this->window->getSize());

//         float x_per = float(event.size.width)/windowSize.x;
//         float y_per = float(event.size.height)/windowSize.y;

//         float newRatio = float(event.size.height) / float(event.size.width);

//         this->view->setSize(sf::Vector2f(viewSize.x, viewSize.x * newRatio));
//         this->view->setCenter(center);

//     }
// }

}