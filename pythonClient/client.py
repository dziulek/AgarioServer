from gameState import MyInfo, GameState, Player
from parseData import parse, fillMyData
import arcade

import socket
import sys
import threading
import time

closeClient = False
#play, wait, end
STATE = {
    'wait' : 0,
    'play' : 1,
    'end' : 2
}

myInfo = MyInfo()
game = GameState()

#locks
game_lock = threading.Lock()
myInfo_lock = threading.Lock()

SEND_FREQUENCY = 30.0

def writeToServerRoutine(server_socket):

    global closeClient
    global myInfo

    t = time.process_time()

    while closeClient == False:

        myInfo_lock.acquire()
        buf = fillMyData(myInfo)
        
        myInfo_lock.release()
        
        elapsed_time = time.process_time() - t
        if elapsed_time > 1 / SEND_FREQUENCY:
            t = time.process_time()
            server_socket.send(bytearray(buf, 'utf-8'))
            # print(buf)
    closeClient = True

def handleConnection(server_socket):

    writeThread = threading.Thread(target=writeToServerRoutine, args=(server_socket,), daemon=True)

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
        # print(data)
        
        game_lock.acquire()
        game.clear()
        parse(data, game)
        game_lock.release()

def connectToServer():

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Socket created")
    except socket.error as err:
        print("socket creation failed with error %s" %(err))

    s.connect((sys.argv[1], int(sys.argv[2])))

    print("succesfully connected to server")

    thread = threading.Thread(target=handleConnection, args=(s,), daemon=True)

    thread.start()

def main():

    global STATE
    global game
    global myInfo


if __name__ == "__main__":

    main()