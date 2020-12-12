#include "shape.hpp"

namespace agario{
    namespace shapes{

        const float Shape::getArea() const{
    
            return this->area;
        }

        const glm::vec2 Shape::getPosition() const{

            return this->position;
        }

        void Shape::setPosition(const glm::vec2 newPos){

            this->position = newPos;
        }

        void Shape::move(const glm::vec2 vec){

            this->position = glm::vec2(position.x + vec.x, position.y + vec.y);
        }

        void Shape::setResultantForce(const glm::vec2 vec){

            this->resultantForce = vec;
        }

        glm::vec2 Shape::getResultantForce(){
            return this->resultantForce;
        }

        // std::pair<glm::vec2, glm::vec2> Shape::retForcesBetweenTwoShapes(const Shape & s1, const Shape & s2){
        //     //default calculation based only center of mass
        // }   
    }//shapes namespace
}//agario namespace


