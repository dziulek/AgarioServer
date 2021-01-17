#ifndef DATA_FORMAT_SERVER_HPP
#define DATA_FORMAT_SERVER_HPP

#include "sendDataFormat.hpp"
#include "../engine/agario_engine.hpp"

struct clientInfo;

class DataFormatServer : public SendDataFormat{

public:

    void appendPlayer(agario::Player * player);

    void extractClientInfo(clientInfo & cinfo);
};

#endif