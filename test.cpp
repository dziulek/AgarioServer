// #include "map.hpp"
// #include "renderer.hpp"
// #include "SFMLRenderer.hpp"
#include <vector>
#include <iostream>

class A{

public:

    void fun(){
        std::cout<<"i am base"<<std::endl;
    }
};

class B : public A{

    int a = 5;

};

int main(){

    A a;
    B b;
    b.fun();    
    
    return 0;
}