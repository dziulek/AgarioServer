#ifndef DATA_FORMATTER
#define DATA_FORMATTER

#include "../lib/AgarioEngine/src/agario_engine.hpp"
#include "dataInterface.hpp"

template<class T>
class DataFormatter{

private:

    T obj;

    void addMapInformation(agario::Player * player);
    void addStatsInformation(agario::Player * player);
    void addPlayerInformation(agario::Player * player);

public:

    void setValue(T & t){this.obj = t;}
    T & getValue(){ return this->obj;}

};

#endif