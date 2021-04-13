#ifndef JSON_DATA_FORMAT_HPP
#define JSON_DATA_FORMAT_HPP

#include "dataFormatter.hpp"
#include "../lib/json/include/nlohmann/json.hpp"

using namespace nlohmann;

class JsonDataFormatter : public DataInterface{

private:

    json data;

    void addMapInformation(agario::Player * player);
    void addStatsInformation(agario::Player * player);
    void addPlayerInformation(agario::Player * player);

public:

    void addMapInformation(json & data, agario::Player * player);
    
    void clearCurrentData() override;
    void fillDataForClient(Client * client) override;
    void interpretClientData(clientInfo & cinfo) override;
};

#endif