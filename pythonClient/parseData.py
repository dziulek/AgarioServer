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
    'view' : 'v'
}

def parse(data, game):

    game.clear()

    player = gameState.Player()
    words = data.split(':')

    minis = np.array([])
    view = np.array([])

    i = 0

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
            word_state = word
            continue

        if current_state == state_dictionary['nickname']:
            player.addNickname(word)
        elif current_state == state_dictionary['coordinates']:
            player.addCoordinate(float(word))
        elif current_state == state_dictionary['minis']:
            np.append(minis, float(word))
        elif current_state == state_dictionary['view']:
            game.addViewCoord(float(word))
        elif current_state == state_dictionary['state']:
            player.setState(bool(word))
    
    if minis is not None:
        game.map['minis'] = np.reshape(minis, (len(game.map['minis'])//3, 3))
        for i in range(len(game.map['minis'])):
            game.map['minis'][i][1] = -game.map['minis'][i][1]

    # if game.view is not None and len(game.view) == 4:
    #     game.view[1] = -game.view[1]
    #     game.view[3] = -game.view[3]

def fillMyData(myInfo):

    text = []
    mouse = SEPARATOR.join([str(myInfo.attributes['mouse'][0]), str(myInfo.attributes['mouse'][1])])   
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
            