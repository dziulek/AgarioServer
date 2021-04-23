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
    std::vector<u_int32_t> minis_color;

    for(int i = mini_range.first.first; i < mini_range.second.first; i++){

        for(int j = mini_range.first.second; j < mini_range.second.second; j++){

            for(auto & m : client->getGame()->getMap()->minis[j][i]){
                
                xMinis.push_back((int)m.get()->getPosition().x);
                yMinis.push_back((int)m.get()->getPosition().y);
                minis_color.push_back(m.get()->getColor());
            }    
        }
    }

    //players
    std::vector<float> xCoordinates, yCoordinates;
    std::vector<float> radius;

    for(int i = 0; i < client->getGame()->getnOfPlayers(); i++){
        
        auto * p = &client->getGame()->getPlayer(i);
        
        this->data["players"][std::to_string(i)]["nickname"] = p->getNickname();
        this->data["players"][std::to_string(i)]["color"] = (u_int32_t)p->getColor();
        
        xCoordinates.clear();xCoordinates.shrink_to_fit();
        yCoordinates.clear();yCoordinates.shrink_to_fit();
        radius.clear();radius.shrink_to_fit();

        for(int j = 0; j < p->getSize(); j++){
            xCoordinates.push_back(JsonDataFormatter::roundFloat((*p)[j].getPosition().x));
            yCoordinates.push_back(JsonDataFormatter::roundFloat((*p)[j].getPosition().y));
            radius.push_back(JsonDataFormatter::roundFloat((*p)[j].getRadius()));
        }
        this->data["players"][std::to_string(i)]["blobs"]["x"] = xCoordinates;
        this->data["players"][std::to_string(i)]["blobs"]["y"] = yCoordinates;
        this->data["players"][std::to_string(i)]["blobs"]["radius"] = radius;
    }

    this->data["map"]["minis"]["x"] = xMinis;
    this->data["map"]["minis"]["y"] = yMinis;
    this->data["map"]["minis"]["radius"] = MINI_RADIUS;
    this->data["map"]["minis_color"] = minis_color;

    std::vector<int> xBomb;
    std::vector<int> yBomb;

    for(auto & bomb : client->getGame()->getMap()->bombs){

        xBomb.emplace_back((int)bomb.get()->getPosition().x);
        yBomb.emplace_back((int)bomb.get()->getPosition().y);
    }

    this->data["map"]["bombs"]["x"] = xBomb;
    this->data["map"]["bombs"]["y"] = yBomb;
    this->data["map"]["bombs"]["radius"] = BOMB_RADIUS;

    std::vector<float> xAbandoned;
    std::vector<float> yAbandoned;
    radius.clear();
    radius.shrink_to_fit();

    for(auto & a : client->getGame()->getMap()->abandoned){
        xAbandoned.emplace_back(JsonDataFormatter::roundFloat(a.get()->getPosition().x));
        yAbandoned.emplace_back(JsonDataFormatter::roundFloat(a.get()->getPosition().y));
        radius.push_back(JsonDataFormatter::roundFloat(a.get()->getRadius()));
    }

    this->data["map"]["abandoned"]["x"] = xAbandoned;
    this->data["map"]["abandoned"]["y"] = yAbandoned;
    this->data["map"]["abandoned"]["radius"] = radius;
} 

void JsonDataFormatter::addStatsInformation(Player * player){


}

void JsonDataFormatter::addPlayerInformation(Player * player){
    
    auto view = player->getView();

    float view_size = std::max(view.second.y - view.first.y, view.second.x - view.first.x);

    this->data["you"]["view"] = {view.first.x, view.first.y, view.first.x + view_size, view.first.y + view_size};

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
            cinfo.w_action = this->data["eject"].get<bool>();

            if(cinfo.divide_action){
                client->getPlayer()->divideObject();
            }
            if(cinfo.w_action){
                client->getGame()->wAction(client->getPlayer());
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
        std::cerr << "something wrong" << std::endl;
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

float JsonDataFormatter::roundFloat(float value, int decimal){

    return int(value * pow(10, decimal)) / pow(10, decimal); 
}