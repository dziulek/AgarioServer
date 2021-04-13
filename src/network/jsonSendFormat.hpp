#ifndef JSON_DATA_FORMAT_HPP
#define JSON_DATA_FORMAT_HPP

#include "dataFormatter.hpp"
#include "../lib/json/single_include/nlohmann/json.hpp"

#include <string>

using namespace nlohmann;

class JsonDataFormatter : public DataInterface{

private:

    json data;

    void addMapInformation(Client * client);
    void addStatsInformation(agario::Player * player);
    void addPlayerInformation(agario::Player * player);

public:

    JsonDataFormatter(const char * buf){

        this->data = std::string(buf);
    }

    JsonDataFormatter(){

    }

    virtual ~JsonDataFormatter(){}

    void addMapInformation(json & data, agario::Player * player);
    
    void clearCurrentData() override;
    void fillDataForClient(Client * client) override;
    void interpretClientData(clientInfo & cinfo) override;

    void setData(const char * buf){this->data = std::string(buf);}
    void setData(const std::string s){this->data = s;}

    const int getRequestType();
    const char * getCharArray(){return this->data.dump().c_str();}
    long getCharNo(){return this->data.dump().length();}
};

#endif