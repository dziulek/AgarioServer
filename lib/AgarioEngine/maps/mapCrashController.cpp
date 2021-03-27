#include "mapCrashController.hpp"

namespace agario{

using namespace shapes;

void MapCrashController::update(){

    //naive version, begin with the simplest algorithm
    for(PlayerObject * p1 : this->getMap()->playerObjects){

        for(PlayerObject * p2 : this->getMap()->playerObjects){
            
            //collision with player itself is calculated in another loop
            if(p1 == p2)
                break;
            for(int i1 = 0; i1 < p1->getSize(); i1++){

                for(int i2 = 0; i2 < p2->getSize(); i2++){



                    float distance = glm::length((*p1)[i1].getPosition() - (*p2)[i2].getPosition());
                    if(distance < std::max((*p1)[i1].getRadius(), (*p2)[i2].getRadius()) && 
                                                    std::max((*p1)[i1].getArea(), (*p2)[i2].getArea()) * 0.85 > std::min((*p1)[i1].getArea(), (*p2)[i2].getArea())){
                        //handle crash
                        if(crashCalculate((*p1)[i1], (*p2)[i2])){

                            float m = std::min((*p1)[i1].getArea(), (*p2)[i2].getArea());
                            if((*p1)[i1].getArea() < (*p2)[i2].getArea()){
                                
                                p1->deleteIthElement(i1);
                                i1--;
                                (*p2)[i2].addMass(m);
                            }
                            else {

                                p2->deleteIthElement(i2);
                                i2--;
                                (*p1)[i1].addMass(m);
                         
                            }
                        }
                    }
                }
            }
        }
    }

    //collision with player itself
    std::vector<int> indexesToDelete;
    for(PlayerObject * p : this->getMap()->playerObjects){

        indexesToDelete.clear();
        indexesToDelete.shrink_to_fit();
        if(!p->canMerge(std::chrono::steady_clock::now()))
            continue;
            
        for(int i = 0; i < p->getSize() - 1; i++){

            for(int j = i + 1; j < p->getSize() ; j++){
                
                if(std::find(indexesToDelete.begin(), indexesToDelete.end(), i) != indexesToDelete.end() ||
                        std::find(indexesToDelete.begin(), indexesToDelete.end(), j) != indexesToDelete.end())
                            continue;

                float distance = glm::length((*p)[i].getPosition() - (*p)[j].getPosition());
                if(distance < std::max((*p)[i].getRadius(), (*p)[j].getRadius())){

                    float m = std::min((*p)[i].getArea(), (*p)[j].getArea());
                    if((*p)[i].getArea() < (*p)[j].getArea()){
                        
                        indexesToDelete.push_back(i);
                        (*p)[j].addMass(m);
                    }
                    else {

                        indexesToDelete.push_back(j);
                        (*p)[i].addMass(m);
                    }
                }
            }
        }

        std::sort(indexesToDelete.begin(), indexesToDelete.end());

        for(int i = indexesToDelete.size() - 1; i >= 0 ; i--)
            p->deleteIthElement(indexesToDelete[i]);
    }



    for(PlayerObject * p : this->getMap()->playerObjects){

        for(int i = 0; i < p->getSize(); i++){

            for(std::vector<std::unique_ptr<MoveableCircle>>::iterator a = this->getMap()->abandoned.begin(); a!=this->getMap()->abandoned.end(); a++){

                float distance = glm::length((*p)[i].getPosition() - a->get()->getPosition());
                if(distance < std::max(a->get()->getRadius(), (*p)[i].getRadius()) && a->get()->getArea() < 0.85 * (*p)[i].getArea()){

                    float m = a->get()->getArea();
                    (*p)[i].addMass(m);
                    a->reset();
                    *a = std::move(this->getMap()->abandoned.back());
                    this->getMap()->abandoned.pop_back();
                    a--;
                    
                }
            }            
        }
    }
}

bool MapCrashController::crashCalculate(MoveableCircle & b1, MoveableCircle & b2){

    float d = glm::length(b2.getPosition() - b1.getPosition());
    float R = std::max(b2.getRadius(), b1.getRadius());
    float r = std::min(b1.getRadius(), b2.getRadius());

    float alpha1 = acos(-(r * r - R * R - d * d) / (2.0f * R * d));
    float alpha2 = acos(-(R * R - r * r - d * d) / (2.0f * r * d));

    float P_1 = R * R * ( 2.0f * alpha1 - sin(2.0f * alpha1)) / 2.0f;
    float P_2 = r * r * ( 2.0f * alpha2 - sin(2.0f * alpha2)) / 2.0f;

    return P_1 + P_2 > 0.75 * std::min(b1.getArea(), b2.getArea()) ? true : false;
}

}