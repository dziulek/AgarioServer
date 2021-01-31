import copy
import numpy as np

class Player:
    def __init__(self):
        self.nickname = 'Unnamed_cell'
        self.coordinates = np.array([])
        self.state = False
    def clear(self):
        self.nickname = ''
        self.coordinates = np.array([])
        self.state = False

    def addCoordinate(self, coord):
        self.coordinates = np.append(self.coordinates, coord)

    def addNickname(self, nick):
        self.nickname = nick
    
    def setState(self, state):
        self.state = state


class GameState:
    def __init__(self):
        self.myPlayer = None
        self.players = []
        self.map = {'minis' : np.array([])}
        self.view = np.array([])
    
    def clear(self):
        self.myPlayer = None
        self.players = []
        self.map = {'minis' : np.array([])}
        
    def appendPlayer(self, player):
        self.players.append(copy.deepcopy(player))
    
    def appendMe(self, me):
        self.myPlayer = copy.deepcopy(me)

    def addMap(self, width, height, minis):
        self.map['width'] = width
        self.map['height'] = height
        self.map['minis'] = copy.deepcopy(minis)

    def addViewCoord(self, coord):
        self.view = np.append(self.view, coord)

class MyInfo:
    def __init__(self):
        self.attributes = {}
        self.attributes['waction'] = 0
        self.attributes['divide'] = 0

    def addWAction(self):
        self.attributes['waction'] = 1
    
    def addMousePosition(self, vector):
        self.attributes['mouse'] = copy.deepcopy(vector)
    
    def addDivideAction(self):
        self.attributes['divide'] = 1

    def addState(self, state):
        self.attributes['state'] = state


def main():

    nickname = 'siemano'
    player = Player()
    player.addNickname(nickname)

    nickname = ''

    print(player.nickname)

    gameState = GameState()

    gameState.appendMe(player)

    player.nickname = 'nie'

    print(gameState.myPlayer.nickname)

if __name__ == "__main__":

    main()


    