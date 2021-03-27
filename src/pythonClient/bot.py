import random
import sys
from client import connectToServer
from gameState import MyInfo, GameState
from parseData import parse, fillMyData
import time
import numpy as np
import math

FACTOR = 100000

def main():

    botInfo = MyInfo()
    board = GameState()
    socket = connectToServer()

    closeClient = False

    nickname = "bot"

    socket.send(bytearray('nickname:' + nickname, 'utf-8'))
    #czekamy na dane które ptrzebne są tylko raz, w tym przypadku tylko wysokość i szerokośc mapy
    confirmation = socket.recv(50)
    data = confirmation.decode()
    empty, width, height, empty = data.split(':')

    dir_x, dir_y = float(width)/2, float(height) / 2

    botInfo.addMousePosition([0, 0])

    while closeClient == False:

        time.sleep(1.0/60)
        #=================send
        buf = fillMyData(botInfo)
        try:
            socket.send(bytearray(buf, 'utf-8'))
        except BrokenPipeError:
            raise BrokenPipeError
        #=================send

        #=================listen
        try:
            buf = socket.recv(100000)
        except OSError:
            raise OSError
        # print(buf)
        
        if len(buf) == 0:
            closeClient = True
        data = buf.decode()
        # print(len(data))
        board.clear()
        parse(data, board)
        #=================listen
        if board.playerState == False:
            break

        center_x = (board.view[0] + board.view[2]) / 2
        center_y = (board.view[1] + board.view[3]) / 2

        minDistance = 1e9
        for mini in board.map['minis']:
            if math.sqrt((center_x - mini[0]) * (center_x - mini[0]) + (center_y - mini[1]) * (center_y - mini[1])) < minDistance:
                dir_x, dir_y = mini[0], mini[1]
        
        botInfo.addMousePosition([dir_x, dir_y])


if __name__ == "__main__":

    main()
