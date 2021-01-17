#include "SFMLRenderer.hpp"
#include "engine/game.hpp"
#include "mouseObserver.hpp"
#include "engine/maps/mapMiniController.hpp"
#include "engine/maps/mapCrashController.hpp"
#include "engine/maps/mapPlayerMovement.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "network/server.hpp"


using namespace agario;

int main(){

    srand(time(NULL));

    Game game;

    game.addPlayer();

    SFMLRenderer rend(game);
    MouseObserver mouse(&rend);

    MapMiniController mini_cont(game.getMap());

    MapPlayerMovement player_movement(game.getMap());

    game.getMap()->addController(&mini_cont);
    game.getMap()->addController(&player_movement);

    while(rend.getWindow()->isOpen()){

        sf::Event event;
        while (rend.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rend.getWindow()->close();
        }

        mouse.update(&game.getPlayer(0));

        rend.getWindow()->clear();

        game.mainLoop(1.0f / 30);

        rend.drawMap();

        rend.getWindow()->display();

        rend.getWindow()->setFramerateLimit(60);
    }

    return 0;
}