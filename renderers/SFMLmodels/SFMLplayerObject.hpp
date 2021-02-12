#ifndef SFML_PLAYER_OBJECT_HPP
#define SFML_PLAYER_OBJECT_HPP

#include "../engine/playerObject.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

namespace SFMLshapes{

class PlayerObject{

public:
  
    void draw(sf::RenderWindow & win, sf::View & view, agario::PlayerObject & player);

};

}

#endif