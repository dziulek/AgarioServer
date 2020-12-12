#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "glm/glm.hpp"
#include <utility>

namespace agario{

namespace shapes{

class Shape {

protected:

    float area;
    glm::vec2 position;
    glm::vec2 resultantForce;

public:

    virtual const float getArea() const;
    const glm::vec2 getPosition() const;
    void setPosition(const glm::vec2 newPos);
    virtual void move(const glm::vec2 vec);
    virtual void setResultantForce(const glm::vec2 vec);
    virtual glm::vec2 getResultantForce();
    //static std::pair<glm::vec2, glm::vec2> retForcesBetweenTwoShapes(const Shape & s1, const Shape & s2);

};

}//shapes namespace 

}//agario namespace



#endif