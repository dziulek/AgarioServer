#include "jsonSendFormat.hpp"

using namespace nlohmann;
using namespace agario;


void JsonDataFormatter::addMapInformation(Player * player){

} 

void JsonDataFormatter::addStatsInformation(Player * player){

}

void JsonDataFormatter::addPlayerInformation(Player * player){

}

void JsonDataFormatter::clearCurrentData(){

    this->data.clear();
}

void JsonDataFormatter::fillDataForClient(Client * client){

    this->clearCurrentData();
    this->addMapInformation(client->getPlayer());
    this->addPlayerInformation(client->getPlayer());
    this->addStatsInformation(client->getPlayer());

    //perhaps some more in the future
}

void JsonDataFormatter::interpretClientData(clientInfo & cinfo){

    cinfo.divide_action = this->data["divide"];
    cinfo.mousePosition = glm::vec2(this->data["mouse"][0], this->data["mouse"][1]);
    // cinfo.state = this->data["state"];
    cinfo.w_action = this->data["eject"];
}