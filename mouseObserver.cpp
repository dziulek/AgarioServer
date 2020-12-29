#include "mouseObserver.hpp"


namespace agario{

using namespace shapes;

void MouseObserver::update(Player * player){

    //update position of the mouse if needed
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->renderer->getWindow());

    this->getRenderer()->getGame()->setPlayerMousePosition(player, {mousePos.x, mousePos.y});
};

}