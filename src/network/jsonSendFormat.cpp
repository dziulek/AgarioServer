#include "jsonSendFormat.hpp"

using namespace nlohmann;
using namespace agario;


void JsonDataFormatter::addMapInformation(Client * client){

    //minis
    std::pair<std::pair<int, int>, std::pair<int, int>> mini_range = client->getGame()->getMap()->getMiniRects(
        client->getPlayer()->getView().first, client->getPlayer()->getView().second
    );

    std::vector<int> xMinis;
    std::vector<int> yMinis;

    for(int i = mini_range.first.first; i < mini_range.second.first; i++){

        for(int j = mini_range.first.second; j < mini_range.second.second; j++){

            for(auto & m : client->getGame()->getMap()->minis[j][i]){
                
                xMinis.emplace_back((int)m.get()->getPosition().x);
                yMinis.emplace_back((int)m.get()->getPosition().y);
            }    
        }
    }

    //players
    std::vector<int> xCoordinates(client->getPlayer()->getSize()), yCoordinates(client->getPlayer()->getSize());

    for(int i = 0; i < client->getGame()->getnOfPlayers(); i++){
        
        auto * p = &client->getGame()->getPlayer(i);
        
        this->data["players"][std::to_string(i)]["nickname"] = p->getNickname();
        this->data["players"][std::to_string(i)]["color"] = p->getColor();
        // this->data["player"][std::to_string(i)]["state"] = p->getState();
        
        for(int j = 0; j < p->getSize(); j++){
            xCoordinates[j] = (int)(*p)[j].getPosition().x;
            yCoordinates[j] = (int)(*p)[j].getPosition().y;
        }
        this->data["players"][std::to_string(i)]["blobs"]["x"] = xCoordinates;
        this->data["players"][std::to_string(i)]["blobs"]["y"] = yCoordinates;
    }

    this->data["map"]["minis"]["x"] = xMinis;
    this->data["map"]["minis"]["y"] = yMinis;

    std::vector<int> xBomb;
    std::vector<int> yBomb;

    for(auto & bomb : client->getGame()->getMap()->bombs){

        xBomb.emplace_back((int)bomb.get()->getPosition().x);
        yBomb.emplace_back((int)bomb.get()->getPosition().y);
    }

    this->data["map"]["bombs"]["x"] = xBomb;
    this->data["map"]["bombs"]["y"] = yBomb;

    std::vector<int> xAbandoned;
    std::vector<int> yAbandoned;

    for(auto & a : client->getGame()->getMap()->abandoned){
        xAbandoned.emplace_back((int)a.get()->getPosition().x);
        yAbandoned.emplace_back((int)a.get()->getPosition().y);
    }

    this->data["map"]["abandoned"]["x"] = xAbandoned;
    this->data["map"]["abandoned"]["y"] = yAbandoned;
} 

void JsonDataFormatter::addStatsInformation(Player * player){


}

void JsonDataFormatter::addPlayerInformation(Player * player){
    
    auto view = player->getView();
    this->data["you"]["view"] = {view.first.x, view.first.y, view.second.x, view.second.y};

    this->data["you"]["state"] = player->getState();
}

void JsonDataFormatter::clearCurrentData(){

    this->data.clear();
}

void JsonDataFormatter::fillDataForClient(Client * client){

    this->clearCurrentData();
    this->addMapInformation(client);
    this->addPlayerInformation(client->getPlayer());
    this->addStatsInformation(client->getPlayer());

    //perhaps some more in the future
}

void JsonDataFormatter::interpretClientData(Client * client){

    clientInfo cinfo;
    try{
        if(this->data["type"].get<std::string>() == "data"){
            
            cinfo.divide_action = this->data["divide"].get<bool>();
            auto tempVec = this->data["mouse"].get<std::vector<float>>();
            cinfo.mousePosition = glm::vec2(tempVec.front(), tempVec.back());

            // cinfo.state = this->data["state"];
            cinfo.w_action = this->data["eject"].get<float>();

            if(cinfo.divide_action){
                client->getPlayer()->divideObject();
            }
            if(cinfo.w_action){
                client->getPlayer()->wAction();
            }

            client->getPlayer()->mousePosition = cinfo.mousePosition;
            
            fillDataForClient(client);
            this->data["type"] = "data";
        }
        else if(!strcmp(this->data["type"].get<std::string>().c_str(),"want_play")){

            client->getPlayer()->setNickname(this->data["nickname"].get<std::string>());
            client->getPlayer()->setColor();

            this->data.clear();
            this->data["type"] = "want_play";
            this->data["map"]["height"] = client->getGame()->getMap()->height;
            this->data["map"]["width"] = client->getGame()->getMap()->width;
        }
        else if(this->data["type"].get<std::string>() == "want_observe"){

            //to do
        }
        else {
            std::cerr << "uknown type" <<std::endl;
        }
    }
    catch(json::type_error & e){
        //invalid request
        std::cerr <<e.what() <<std::endl;
    }


}

const int JsonDataFormatter::getRequestType(){

    try
    {
        if(this->data["type"].get<std::string>() == "data") return this->DATA;
        if(this->data["type"].get<std::string>() == "want_play") return this->WANT_PLAY;
        if(this->data["type"].get<std::string>() == "want_observe") return this->WANT_OBSERVE;
    }
    catch(const detail::type_error& e)
    {
        return -1;
    }
    
    return -1;
}