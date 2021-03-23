#ifndef DATA_FORMAT_SERVER_HPP
#define DATA_FORMAT_SERVER_HPP

#include "sendDataFormat.hpp"
#include "../engine/agario_engine.hpp"
#include "client.hpp"

struct clientInfo;

/*
Klasa DataFormatServer dziedziczy po SenDataFormat, 
udostępnia funkcje do wypełniania bufora danych przez serwer do klienta oraz interpretuje dane od klienta. 
*/

class DataFormatServer : public SendDataFormat{

public:

    //Dodaje gracza do bufora
    void appendPlayer(agario::Player * player);

    //Dodaje widok, który widzi gracz
    void appendView(agario::Player * player);

    void appendMass(agario::Player * player);

    //Dodaje małe kulko na mapie
    void appendMinis(agario::Game * game, agario::Player * player);

    //Interpretuje dane od klienta, wypełnia strukturę cinfo, opisującego klienta
    void extractClientInfo(clientInfo & cinfo);

    //Dodaje stan gracza
    void appendState(agario::Player * player);
};

#endif