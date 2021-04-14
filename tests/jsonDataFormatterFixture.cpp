#include "gtest/gtest.h"
// #include "gmock/gmock.h"
#include "../src/network/jsonSendFormat.hpp"
#include "../lib/AgarioEngine/src/agario_engine.hpp"

sockaddr_storage s;

class jsonDataFormatterFixture : public ::testing::Test{

public:
    
    jsonDataFormatterFixture(){

        this->jsonBuf = new JsonDataFormatter();
        this->player = new agario::Player(glm::vec2(0.f,0.f), "foo");
        this->game = new agario::Game();
        this->client = new Client("", 0, &s);
        this->client->setGame(game);
        this->client->setPlayer(player);
    }

    static void SetUpTestSuite(){
        
    }

    static void TearDownTestSuite(){

    }

    void SetUp(){
        //
    }

    void TearDown(){

    }

    virtual ~jsonDataFormatterFixture(){

        delete jsonBuf;
        delete player;
        delete game;
        delete client;
    }

    JsonDataFormatter * jsonBuf;
    clientInfo cinfo;
    agario::Player * player;
    agario::Game * game;
    Client * client;
};

TEST_F(jsonDataFormatterFixture, request_want_play){

    json temp;
    temp["type"] = "want_play";
    temp["nickname"] = "test";
    
    jsonBuf->setData(temp.dump());
    ASSERT_STREQ(jsonBuf->getBuf()["type"].get<std::string>().c_str(), "want_play");
    
    jsonBuf->interpretClientData(client);

    ASSERT_FLOAT_EQ(jsonBuf->getBuf()["map"]["width"].get<float>(), game->getMap()->width);
    ASSERT_FLOAT_EQ(jsonBuf->getBuf()["map"]["height"].get<float>(), game->getMap()->height);

    ASSERT_STREQ(temp["nickname"].get<std::string>().c_str(), player->getNickname().c_str());
}