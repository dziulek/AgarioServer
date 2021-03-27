#ifndef PLAYER_OBJECT_HPP
#define PLAYER_OBJECT_HPP

#include "allshapes.hpp"
#include "gameObject.hpp"
#include "maps/map.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <utility>
#include <chrono>

namespace agario{

using namespace shapes;

class PlayerObject : public GameObject{

private:

    std::vector<std::unique_ptr<MoveableCircle>> blobs;
    float totalArea;
    std::pair<std::chrono::steady_clock::time_point, float> last_division;

    float calcSeparationTime();
    
    

public:

    glm::vec2 mousePosition = {1.0f,1.0f};

    PlayerObject(glm::vec2 pos){

        blobs.push_back(std::unique_ptr<MoveableCircle>(new MoveableCircle(pos, 3* MIN_PLAYER_RADIUS)));

        totalArea = blobs.back().get()->getArea();
    }
    virtual ~PlayerObject(){}

    MoveableCircle & operator[](int t);

    std::vector<std::unique_ptr<MoveableCircle>> * getBlobs(){ return &blobs; }
    bool canMerge(std::chrono::steady_clock::time_point tp);
    
    void deleteIthElement(int i);
    void resetIthElement(int i);

    void setVelocities();

    void divideObject() override;
    void addMass(const float mass) override;
    void addMass(const float mass, int mcIndex);
    void move(const float dTime) override;
    void setPosition(const glm::vec2 pos) override;
    void wAction();
    std::pair<glm::vec2, glm::vec2> getMinRectangle();

    float bombAction(const unsigned int blob_index);
    float bombAction(std::unique_ptr<MoveableCircle> & mv);
    float getTotalArea();
    int getSize();
};

}


#endif