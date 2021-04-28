from pythonClient.gameState import Player, GameState
import numpy as np
import json

SEPARATOR = ':'

state_dictionary = {
    'player' : 'p',
    'state' : 's',
    'play_in' : 'i',
    'play_out' : 'o',
    'nickname' : 'n',
    'map' : 'm',
    'minis' : 'q',
    'coordinates' : 'c',
    'mouse' : 'm',
    'divide_action' : 'd',
    'w_mass' : 'w',
    'myplayer' : 'u',
    'view' : 'v', 
    'color' : 't'
}

DATA = "data"
START_INFO = "want_play"
STATS = "stats"

def parse(data, game):

    try:
        jsonData = json.loads(data)
    except:
        raise TypeError

    if jsonData["type"] == DATA:    

        game.clear()
        tempPlayer = Player()
        playerList = jsonData["players"]

        #players
        for player in playerList:
            tempPlayer.clear()
            tempPlayer.setBlobsCoordinates(
                np.array(list(zip(playerList[player]["blobs"]["x"], playerList[player]["blobs"]["y"], playerList[player]["blobs"]["radius"])), dtype=float)
            )
            tempPlayer.addNickname(playerList[player]["nickname"])
            tempPlayer.color = playerList[player]["color"]
            game.appendPlayer(tempPlayer)
        
        #map
        #minis
        minisNo = len(jsonData["map"]["minis"]["x"])
        minis = np.array(list(zip(jsonData["map"]["minis"]["x"], jsonData["map"]["minis"]["y"], minisNo * [jsonData["map"]["minis"]["radius"]])))
        minis_color = np.array(jsonData["map"]["minis_color"])
        #abandoned
        abandoned = np.array(list(zip(jsonData["map"]["abandoned"]["x"], jsonData["map"]["abandoned"]["y"], jsonData["map"]["abandoned"]["radius"])))
        abandoned = np.dot(abandoned, 0.01)
        #bombs
        bombsNo = len(jsonData["map"]["bombs"]["x"])
        bombs = np.array(list(zip(jsonData["map"]["bombs"]["x"], jsonData["map"]["bombs"]["y"], bombsNo * [jsonData["map"]["bombs"]["radius"]])))
        #view
        view = jsonData["you"]["view"]
        if len(view) == 4:
            view = np.reshape(np.array(view, dtype=float), (2,2))
            view = np.dot(view, 0.01)

        state = bool(int(chr(jsonData["you"]["state"])))

        game.addMap(minis, bombs, abandoned, minis_color)
        game.setView(view)
        
        game.playerState = state

    if jsonData["type"] == START_INFO:

        return jsonData["map"]["width"], jsonData["map"]["height"]
        

    if jsonData["type"] == STATS:

        stats = None




def fillMyData(myInfo, request_type):

    jsonData1 = {}

    jsonData1["type"] = request_type
    jsonData1["divide"] = bool(myInfo.attributes["divide"])
    jsonData1["eject"] = bool(myInfo.attributes["waction"])
    jsonData1["mouse"] = myInfo.attributes["mouse"]

    return json.dumps(jsonData1)

def main():

    pass

if __name__ == "__main__":

    main()
            