#ifndef MINI_HPP
#define MINI_HPP

#include "shape.hpp"
#include "circle.hpp"

namespace agario{

namespace shapes{

class Mini : public Circle{
    
public:

    Mini(const glm::vec2 pos){
        
        centerPosition = pos;
        radius = MINI_RADIUS;

        color = AGARIO_COLORS[rand() % n_colors];
        calculateArea();
    }
    virtual ~Mini(){}
};

}

}



#endif