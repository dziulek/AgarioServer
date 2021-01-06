#include "SFMLRenderer.hpp"
#include "engine/game.hpp"
#include "mouseObserver.hpp"
#include "engine/maps/mapMiniController.hpp"
#include "engine/maps/mapCrashController.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "network/server.hpp"


using namespace agario;

class C{

public:

    float xd;

    C(float x) : xd(x){}
};

class A{


    public:

    std::vector<std::unique_ptr<C>> cc;
    int  a;
    int b;

    A(int a, int b){
        this->a = a;
        this->b = b;

        cc.push_back(std::unique_ptr<C>(new C(3.0)));
    }
};

class B : public A{

public:

    int c;

    B(int a, int b, int c) : A(a,b){
        this->c = c;
    }
};


int main(){

    Server server;

    int status = server.mainLogic();

    if(status == -1){
        return -1;
    }

    return 0;
}