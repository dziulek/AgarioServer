#ifndef DATA_FORMAT_SERVER_HPP
#define DATA_FORMAT_SERVER_HPP

#include "sendDataFormat.hpp"
#include "../engine/agario_engine.hpp"
#include "client.hpp"

struct clientInfo;

class DataFormatServer : public SendDataFormat{

public:

    void appendPlayer(agario::Player * player);

    void appendMyPlayer(agario::Player * player);

    void appendMinis(agario::Game * game, agario::Player * player);

    void extractClientInfo(clientInfo & cinfo);
};

#endif