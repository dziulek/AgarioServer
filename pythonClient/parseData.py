import gameState.GameState as game
import gameState.Player as player
import gameState.MyInfo as myInfo

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
    'myplayer' : 'u'
    'view' : 'v'
}

def parseData(data, gameState):

    gameState.clear()
    player = 
    words = data.split(':')

    minis = np.array()

    first_player = 0

    current_state = 'y'
    for word in words:
        if word == '':
            continue
        elif word == state_dictionary['player']:
            current_state = word
            first_player += 1
            continue
        elif word == state_dictionary['myplayer']:
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

        if current_state == state_dictionary['nickname']:
            player.addNickname(word)
        elif current_state == state_dictionary['coordinates']:
            player.addCoordinate(float(word))
        elif current_state == state_dictionary['minis']
            np.append(minis, float(word))
            