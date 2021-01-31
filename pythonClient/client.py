from gameState import MyInfo, GameState, Player
import parseData
import arcade

import socket
import sys
import threading

closeClient = False
#play, wait, end
STATE = {
    'wait' : 0,
    'play' : 1,
    'end' : 2
}

myInfo = MyInfo()
game = GameState()

def writeToServerRoutine(server_socket):

    global closeClient
    global myInfo
    # while closeClient == False:

    #     # buf = parseData.fillMyData(myInfo)
    #     # server_socket.send(bytearray(buf, 'utf-8'))
    
    # closeClient = True

def handleConnection(server_socket):

    writeThread = threading.Thread(target=writeToServerRoutine, args=(server_socket,), daemon=False)

    writeThread.start()

    listenOnSocket(server_socket)

    writeThread.join()


def listenOnSocket(server_socket):

    global closeClient
    global game
    while closeClient == False:
        buf = server_socket.recv(10000)
        
        if len(buf) == 0:
            closeClient = True
        data = buf.decode()
        
        game.clear()
        parseData.parse(data, game)

def connectToServer():

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Socket created")
    except socket.error as err:
        print("socket creation failed with error %s" %(err))

    s.connect((sys.argv[1], int(sys.argv[2])))

    print("succesfully connected to server")

    thread = threading.Thread(target=handleConnection, args=(s,), daemon=False)

    thread.start()

    thread.join()

def main():

    global STATE
    global game
    global myInfo

    connectToServer()


if __name__ == "__main__":

    main()