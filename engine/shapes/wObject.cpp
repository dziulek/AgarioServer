#include "wObject.hpp"

namespace agario{

namespace shapes{

bool WObject::checkIfStop(){

    return glm::length(this->velocity) > eps ? false : true;
}

void WObject::stopObject(){

    this->velocity = {0.0, 0.0};
    this->isMove = false;
}

void WObject::slowDown(){


}
}//shapes

}//agario