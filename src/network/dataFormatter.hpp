#ifndef DATA_FORMATTER
#define DATA_FORMATTER

#include "../lib/AgarioEngine/src/agario_engine.hpp"
// #include "dataInterface.hpp"

template<class T>
class DataFormatter{

private:

    T obj;

public:

    void setValue(T & t){this.obj = t;}
    T & getValue(){ return this->obj;}

};

#endif