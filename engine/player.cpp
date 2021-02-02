#include "player.hpp"


namespace agario{

using namespace shapes;

std::pair<glm::vec2, glm::vec2> Player::getView(){

    std::pair<glm::vec2, glm::vec2> viewCoord = this->getMinRectangle(), out;

    float x_pad, y_pad;

    x_pad = y_pad = 50;

    out.first = {viewCoord.first.x - x_pad, viewCoord.first.y - y_pad};
    out.second = {viewCoord.second.x + x_pad, viewCoord.second.y + y_pad};

    return out;
}

}