#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../glm/glm.hpp"
#include "../constants.hpp"
#include <utility>

namespace agario{

namespace shapes{

class Shape {

protected:

    float area;

public:

    virtual ~Shape(){};
    virtual const float getArea() const;
    virtual glm::vec2 getPosition() const = 0;
    virtual void calculateArea() = 0;

};

}//shapes namespace 

}//agario namespace



#endif