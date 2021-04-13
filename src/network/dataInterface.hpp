#ifndef DATA_INTERFACE_HPP
#define DATA_INTERFACE_HPP

#include "../lib/AgarioEngine/src/agario_engine.hpp"
#include "client.hpp"
#include "threadFunctions.hpp"




class DataInterface{

protected:




public:

    enum REQUEST_TYPE{
        DATA,
        WANT_PLAY,
        WANT_OBSERVE
    };

    virtual void fillDataForClient(Client * client) = 0;
    virtual void clearCurrentData() = 0;
    virtual void interpretClientData(clientInfo & cinfo) = 0;
};

#endif