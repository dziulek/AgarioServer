import gameState
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
START_INFO = "start_info"
STATS = "stats"

def parse(data, game):

    jsonData = json.loads(data)

    if jsonData["type"] == DATA:

        game.clear()
        tempPlayer = gameState.Player()
        playerList = jsonData["map"]["player"]

        #players
        for player in playerList:
            tempPlayer.clear()
            tempPlayer.addBlobsCoordinates(
                np.array([np.array(player["blobs"]["x"]), 
                np.array(player["blobs"]["y"])]).reshape(len(player["blobs"]["x"]), 2)
            )
            tempPlayer.addNickname(player["nickname"])
            game.appendPlayer(player)
        
        #map
        #minis
        minis = np.array(zip(jsonData["map"]["minis"]["x"], jsonData["map"]["minis"]["y"]))
        #abandoned
        abandoned = np.array(zip(jsonData["map"]["abandoned"]["x"], jsonData["map"]["abandoned"]["y"]))
        #bombs
        bombs = np.array(zip(jsonData["map"]["bombs"]["x"], jsonData["map"]["bombs"]["y"]))

    player = gameState.Player()
    words = data.split(':')

    minis = np.array([])
    colors = np.array([], int)
    view = np.array([])
    map_size = np.array([])

    i = 0
    cmini = 0

    current_state = '-'
    for word in words:
        if word == '':
            continue
        elif word == state_dictionary['player']:
            if i > 0:
                player.coordinates = np.reshape(player.coordinates, (len(player.coordinates) // 3, 3))
                # for i in range(len(player.coordinates)):
                #     player.coordinates[i][1] = -player.coordinates[i][1]
                game.appendPlayer(player)

            player.clear()
            current_state = word
            i += 1
            continue
        elif word == state_dictionary['color']:
            current_state = word
            continue
        elif word == state_dictionary['minis']:
            current_state = word
            continue
        elif word == state_dictionary['nickname']:
            current_state = word
            continue
        elif word == state_dictionary['coordinates']:
            current_state = word
            continue
        elif word == state_dictionary['view']:
            current_state = word
            continue
        elif word == state_dictionary['state']:
            current_state = word
            continue

        if current_state == state_dictionary['nickname']:
            player.addNickname(word)
        elif current_state == state_dictionary['coordinates']:
            player.addCoordinate(float(word))
        elif current_state == state_dictionary['minis']:
            cmini += 1
            if cmini % 4 == 0:
                colors = np.append(colors, int(word, 16))
            else:
                minis = np.append(minis, float(word))
        elif current_state == state_dictionary['view']:
            game.addViewCoord(float(word))
        elif current_state == state_dictionary['state']:
            game.playerState = bool(int(word))
        elif current_state == state_dictionary['color']:
            player.color = int(word, 16)
    
    if minis is not None:
        minis = np.resize(minis, len(minis) // 3 * 3)
        game.map['minis'] = np.reshape(minis, (len(minis)//3, 3))
    if colors is not None:
        game.map['colors'] = colors

def fillMyData(myInfo):

    text = ['data']
    mouse = SEPARATOR.join(['{:.2f}'.format(myInfo.attributes['mouse'][0]), '{:.2f}'.format(myInfo.attributes['mouse'][1])])   
    text.append(state_dictionary['mouse'])
    text.append(mouse)
    text.append(state_dictionary['w_mass'])
    text.append(str(myInfo.attributes['waction']))

    text.append(state_dictionary['divide_action'])
    text.append(str(myInfo.attributes['divide']))

    text.append(state_dictionary['state'])
    text.append(str(myInfo.attributes['state']))

    text = SEPARATOR + SEPARATOR.join(text) + SEPARATOR

    return text

def main():

    a = False


if __name__ == "__main__":

    main()
            