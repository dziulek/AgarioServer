#include "SFMLRenderer.hpp"


namespace agario{

using namespace shapes;

void SFMLRenderer::drawGameObject(GameObject & gameObject){

    sf::CircleShape sparkle;

    for(int i = 0; i < gameObject.getSparklesSize(); i++){

        sparkle.setRadius(gameObject[i].getRadius());
        sparkle.setPosition(gameObject[i].getPosition().x, gameObject[i].getPosition().y);
        this->window->draw(sparkle);
    }
}

void SFMLRenderer::drawMap(TestMap & map){

    //draw background
    this->window->clear();
    //draw lines
    float x = 0.0f, y = 0.0f;

    sf::Transform transformX, transformY;
    transformX.translate(sf::Vector2f(map.cellWidth, 0.0f));
    transformY.translate(sf::Vector2f(0.0f, map.cellWidth));

    sf::Vertex xline[] ={
        sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
        sf::Vertex(sf::Vector2f(0.0f, map.height))
    };

    while(x < map.width){
        this->window->draw(xline, 2, sf::Lines, transformX);
        x += map.cellWidth;
    }

    sf::Vertex yline[] = {
        sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
        sf::Vertex(sf::Vector2f(map.width, 0.0f))
    };

    while(y < map.height){
        this->window->draw(yline, 2, sf::Lines, transformY);
        y += map.cellWidth;
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


}