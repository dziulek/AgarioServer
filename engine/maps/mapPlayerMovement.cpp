#include "mapPlayerMovement.hpp"

namespace agario{

using namespace shapes;

void MapPlayerMovement::update(){

    check_borders();
}

void MapPlayerMovement::check_borders(){

    
    //for each player
    for(auto & playerobject : map->playerObjects){

        //for each blob
        for(int i = 0; i < playerobject->getSize(); i++){

            float xVelocity = (*playerobject)[i].getVelocity().x;
            float yVelocity = (*playerobject)[i].getVelocity().y;
            float xPosition = (*playerobject)[i].getPosition().x;
            float yPosition = (*playerobject)[i].getPosition().y;
            float radius = (*playerobject)[i].getRadius();

            //left border
            if((*playerobject)[i].getPosition().x - (*playerobject)[i].getRadius() < 0)
                (*playerobject)[i].setVelocity({abs(xVelocity), (*playerobject)[i].getVelocity().y});
            //right border
            if((*playerobject)[i].getPosition().x + (*playerobject)[i].getRadius() > map->width)
                (*playerobject)[i].setVelocity({-abs(xVelocity), (*playerobject)[i].getVelocity().y});
            //up border
            if((*playerobject)[i].getPosition().y - (*playerobject)[i].getRadius() < 0)
                (*playerobject)[i].setVelocity({(*playerobject)[i].getVelocity().x, abs(yVelocity)});
            //down border
            if((*playerobject)[i].getPosition().y + (*playerobject)[i].getRadius() > map->height)
                (*playerobject)[i].setVelocity({(*playerobject)[i].getVelocity().x, -abs(yVelocity)});
        }

    }

    float xVel;
    float yVel;

    for(auto & w : map->abandoned){

        xVel = w.get()->getVelocity().x;
        yVel = w.get()->getVelocity().y;

        if(w.get()->getPosition().x - W_RADIUS < 0){
            w.get()->setVelocity({abs(xVel), yVel});
        }
        else if(w.get()->getPosition().x + W_RADIUS > map->width){
            w.get()->setVelocity({-abs(xVel), yVel});
        }
        if(w.get()->getPosition().y - W_RADIUS < 0){
            w.get()->setVelocity({xVel, abs(yVel)});
        }
        else if(w.get()->getPosition().y + W_RADIUS > map->height){
            w.get()->setVelocity({xVel, -abs(yVel)});
        }
    }
}


}