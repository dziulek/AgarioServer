#include "SFMLRenderer.hpp"


namespace agario{

using namespace shapes;

void SFMLRenderer::drawGameObject(const GameObject & gameObject){

    sf::CircleShape sparkle;

    for(int i = 0; i < gameObject.getSparklesSize(); i++){

        sparkle.setRadius(gameObject[i].getRadius());
        sparkle.setPosition(gameObject[i].getPosition());
        this->window.draw(sparkle);
    }
}

void SFMLRenderer::drawMap(const Map & map){

    //draw background
    
    //draw bombs

    //draw minis

}


}