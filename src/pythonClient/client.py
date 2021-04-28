from pythonClient.gameState import MyInfo, GameState, Player
from pythonClient.parseData import parse, fillMyData
from constants import MAX_BUF_LEN
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

# buf = '\0' * MAX_BUF_LEN

def writeToServerRoutine(server_socket):

    global closeClient
    global myInfo

    request_type = 'data'
    buff = fillMyData(myInfo, request_type)
    try:
        server_socket.send(bytearray(buff + '\0', 'utf-8'))
        myInfo.clear()
    except BrokenPipeError:
        raise BrokenPipeError

def handleConnection(server_socket):

    writeThread = threading.Thread(target=writeToServerRoutine, args=(server_socket,), daemon=True)

    writeThread.start()

    listenOnSocket(server_socket)

    writeThread.join()


def listenOnSocket(server_socket):

    global closeClient
    global game

    try:
        buf = server_socket.recv(100000)
    except OSError:
        raise OSError
    
    if len(buf) == 0:
        closeClient = True
        return
    
    data = buf.decode()


    try:
        message_len = int(data[:10])
    except:
        return

    while message_len > len(data):
        try:
            buf = server_socket.recv(MAX_BUF_LEN)
        except OSError:
            raise OSError
        data += buf.decode()

    if len(data) > message_len:
        return

    try:
        if int(data[:10]) == len(data):
            data = data[10:]
            parse(data, game)
    except :
        print('======================================')
        print('data invalid')
        print(data)
        print('======================================')

def connectToServer():

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Socket created")
    except socket.error as err:
        print("socket creation failed with error %s" %(err))

    try:
        s.connect((sys.argv[1], int(sys.argv[2])))
    except ConnectionRefusedError:
        raise ConnectionRefusedError
    except socket.gaierror:
        raise socket.gaierror

    print("succesfully connected to server")

    return s

def main():

    global STATE
    global game
    global myInfo


if __name__ == "__main__":

    main()