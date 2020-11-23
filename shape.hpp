#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace shapes{

class Shape {

protected:

    float area;
    glm::vec2 position;

public:

    virtual const float getArea() const;
    virtual const glm::vec2 getPosition() const;
    virtual void setPosition(const glm::vec2 newPos);
    virtual inline void move(const glm::vec2 vec);

};

}

#endif