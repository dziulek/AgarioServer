#ifndef DATA_INTERFACE_HPP
#define DATA_INTERFACE_HPP

#include "../../lib/AgarioEngine/src/agario_engine.hpp"
#include "client.hpp"

//Struktura zawierająca stan klienta
struct clientInfo{

    char state;
    glm::vec2 mousePosition;
    bool divide_action;
    bool w_action;
};


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
    virtual void interpretClientData(Client * client) = 0;
};

#endif