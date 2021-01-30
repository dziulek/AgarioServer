import copy
import numpy as np

class Player:
    def __init__(self):
        self.nickname = 'Unnamed_cell'
        self.coordinates = np.array()
        self.state = 'wait'
    def clear(self):
        self.nickname = ''
        self.coordinates = np.array()
        self.state = 'wait'
        self.view = np.array()

    def addCoordinate(self, coord):
        np.append(self.coordinates, coord)

    def addNickname(self, nick):
        self.nickname = nick
    
    def setState(self, state):
        self.state = state

    def addViewCoord(self, coord):
        np.append(self.view, coord)


class GameState:
    def __init__(self):
        self.myPlayer = None
        self.players = []
        self.map = {}
    
    def clear(self):
        self.myPlayer = None
        self.players = []
        self.map = {}
        
    def appendPlayer(self, player):
        self.players.append(copy.deepcopy(player))
    
    def appendMe(self, me):
        self.myPlayer = copy.deepcopy(me)

    def addMap(self, width, height, minis):
        self.map['width'] = width
        self.map['height'] = height
        self.map['minis'] = copy.deepcopy(minis)

class MyInfo:
    def __init__(self):
        self.attributes = {}

    def addWAction(self, var):
        self.attribute['waction'] = var
    
    def addMousePosition(self, vector):
        self.attribute['mouse'] = copy.deepcopy(vector)
    
    def addDivideAction(self, var):
        self.attribute['divide'] = var

    def addState(self, state):
        self.attribute['state'] = state


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


    