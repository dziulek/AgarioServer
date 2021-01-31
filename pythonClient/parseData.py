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

    player = None
    words = data.split(':')

    minis = np.array([])

    current_state = '-'
    for word in words:
        if word == '':
            continue
        elif word == state_dictionary['player']:
            if player != None:
                player.coordinates = np.reshape(player.coordinates, (len(player.coordinates) // 3, 3))
                game.appendPlayer(player)

            player = gameState.Player()
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

        if current_state == state_dictionary['nickname']:
            player.addNickname(word)
        elif current_state == state_dictionary['coordinates']:
            player.addCoordinate(float(word))
        elif current_state == state_dictionary['minis']:
            np.append(minis, float(word))
        elif current_state == state_dictionary['player']:
            player.clear()
        elif current_state == state_dictionary['view']:
            game.addViewCoord(float(word))

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

    print(text)

    return SEPARATOR.join(text)

def main():

    a = False


if __name__ == "__main__":

    main()
            