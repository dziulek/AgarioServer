#include "SFMLplayerObject.hpp"

namespace SFMLshapes{

void PlayerObject::draw(sf::RenderWindow & win, sf::View & view, agario::PlayerObject & player){

    win.setView(view);

    for(int i = 0; i < player.getSize(); i++){

        sf::CircleShape c(player[i].getRadius());
        c.setPosition(player[i].getPosition().x,
                    player[i].getPosition().y);

        win.draw(c);
    }
}

}