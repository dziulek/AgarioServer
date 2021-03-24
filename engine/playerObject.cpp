#include "playerObject.hpp"

namespace agario{

using namespace shapes;

void PlayerObject::divideObject(){

    if(blobs.size() <= MAX_PLAYER_SIZE / 2){

        std::vector<std::unique_ptr<MoveableCircle>> tempVec;
        for(auto & b : blobs){
            b.get()->addMass(-b.get()->getArea()/2);
            glm::vec2 new_position = b.get()->getPosition() 
                            + glm::normalize(this->mousePosition - b.get()->getPosition()) * b.get()->getRadius() * 1.1f;
            tempVec.push_back(std::unique_ptr<MoveableCircle>(new MoveableCircle(new_position, b.get()->getRadius()))); 
        }

        for(auto & temp : tempVec){
            this->blobs.push_back(std::move(temp));
            this->blobs.back().get()->setColor(blobs.front()->getColor());
        }   

        this->last_division = {std::chrono::steady_clock::time_point::clock::now(), calcSeparationTime()}; 
    }
        
}

void PlayerObject::addMass(const float mass){

    
}

void PlayerObject::move(const float dTime){

    for(auto & mc : blobs){
        
        mc->move(dTime);
    }
}

float PlayerObject::calcSeparationTime(){
    
    return (this->getTotalArea() / blobs.size()) / 15.0f;
}

bool PlayerObject::canMerge(std::chrono::steady_clock::time_point tp){

    return (std::chrono::duration_cast<std::chrono::seconds>(tp - this->last_division.first).count() 
                    >= this->last_division.second ? true : false);
}

void PlayerObject::setPosition(const glm::vec2 pos){

}

float PlayerObject::getTotalArea(){

    float sum = 0;

    for(auto & mc : blobs){
        sum += mc->getArea();
    }

    return sum;
}

int PlayerObject::getSize(){

    return this->blobs.size();
}

MoveableCircle & PlayerObject::operator[](int t){

    return *blobs[t].get();
}

void PlayerObject::setVelocities(){

    for(auto & b : blobs){

        glm::vec2 v = mousePosition - b.get()->getPosition();

        glm::vec2 before = v;

        // std::cout << before.x << " " << before.y << std::endl;
        if(abs(v.x) < 1.0 && abs(v.y) < 1.0)
            v = {0, 0};
        else v = glm::normalize(v);

        v *= b.get()->calculateVelocityMod();

        b.get()->setVelocity(v);
    }

    if(!canMerge(std::chrono::steady_clock::now())){

        MoveableCircle * temp_b1, * temp_b2;
        for(int i = 0; i < blobs.size() - 1; i++){
            for(int j = i + 1; j < blobs.size(); j++){ 
                
                temp_b1 = blobs[i].get();
                temp_b2 = blobs[j].get();

                if(glm::distance(temp_b1->getPosition(), temp_b2->getPosition()) < temp_b2->getRadius() + temp_b1->getRadius()){

                    glm::vec2 ax = glm::normalize(temp_b2->getPosition() - temp_b1->getPosition()) * 10.0f;

                    temp_b1->setVelocity(temp_b1->getVelocity() - ax);
                    temp_b2->setVelocity(temp_b2->getVelocity() + ax);
                }

            }
        }        
    }
}

void PlayerObject::addMass(const float mass, int mcIndex){

    blobs[mcIndex].get()->addMass(mass);
}

void PlayerObject::deleteIthElement(int i){

    blobs[i].reset();
    blobs[i] = std::move(blobs.back());

    blobs.pop_back();
    blobs.shrink_to_fit();

}

void PlayerObject::resetIthElement(int i){

    blobs[i].reset();
}

std::pair<glm::vec2, glm::vec2> PlayerObject::getMinRectangle(){

    glm::vec2 left_upper = glm::vec2(PLUS_INFINITY, PLUS_INFINITY);
    glm::vec2 down_right = glm::vec2(MINUS_INFINITY, MINUS_INFINITY);

    for(auto & blob : blobs){

        left_upper.x = std::min(left_upper.x, blob.get()->getPosition().x - blob.get()->getRadius());
        left_upper.y = std::min(left_upper.y, blob.get()->getPosition().y - blob.get()->getRadius());

        down_right.x = std::max(down_right.x, blob.get()->getPosition().x + blob.get()->getRadius());
        down_right.y = std::max(down_right.y, blob.get()->getPosition().y + blob.get()->getRadius());
    }

    return {left_upper, down_right};
}

}