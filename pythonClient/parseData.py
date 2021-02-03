import gameState
import numpy as np

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

def parse(data, game):

    game.clear()

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
        elif word == state_dictionary['map']:
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
            game.playerState = bool(word)
        elif current_state == state_dictionary['map']:
            map_size = np.append(map_size, float(word))
        elif current_state == state_dictionary['color']:
            player.color = int(word, 16)
    
    if minis is not None:
        game.map['minis'] = np.reshape(minis, (len(minis)//3, 3))
    if colors is not None:
        game.map['colors'] = colors
    if map_size is not None:
        game.map['width'], game.map['height'] = map_size
    # if game.view is not None and len(game.view) == 4:
    #     game.view[1] = -game.view[1]
    #     game.view[3] = -game.view[3]

def fillMyData(myInfo):

    text = []
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
            