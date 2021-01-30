import gameState.GameState as game
import gameState.Player as player

import pygame
import socket
import sys
import threading

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600


clock = pygame.time.Clock()

from pygame.locals import (
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    KEYDOWN,
    QUIT,
)

closeClient = False
#play, wait, end
STATE = 'wait'

# def drawStartScreen(screen)

def writeToServerRoutine(server_socket):

    global closeClient
    while closeClient == False:

        buf = input()
        if buf == 'close':
            closeClient = True
        server_socket.send(bytearray(buf, 'utf-8'))
    
    closeClint = True

def handleConnection(server_socket):

    writeThread = threading.Thread(target=writeToServerRoutine, args=(server_socket,), daemon=False)

    writeThread.start()

    listenOnSocket(server_socket)

    writeThread.join()


def listenOnSocket(server_socket):

    global closeClient
    while closeClient == False:
        buf = server_socket.recv(1024)
        if len(buf) == 0:
            closeClient = True
        print(buf.decode())

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

def parseData(data):

    data = data.split(':')
    for i in range(len(data))

def main():

    global STATE

    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    screenCenter = (pygame.display.get_surface().get_width()/2, pygame.display.get_surface().get_height()/2)
    base_font = pygame.font.Font(None, 32)
    header_font = pygame.font.Font(None, 100)
    user_name = ''
    header_text = 'Agar.io'
    background = pygame.image.load("background.png")
    imagerect = background.get_rect()

    input_rect = pygame.Rect(screenCenter[0], screenCenter[1], 140, 32)
    running = True

    while running:

        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                    closeClient = True
                elif STATE == 'wait':
                    if event.key == pygame.K_RETURN:
                        STATE = 'play'
                    elif  event.key == pygame.K_BACKSPACE:
                        user_name = user_name[:-1]
                    else:
                        user_name += event.unicode
            if event.type == QUIT:
                running = False
                closeClient = True

            
        screenCenter = (pygame.display.get_surface().get_width()/2, pygame.display.get_surface().get_height()/2)
        mousePosition = pygame.mouse.get_pos()

        blob_direction = (mousePosition[0] - screenCenter[0], mousePosition[1] - screenCenter[1])

        # print(blob_direction)

        screen.fill('black')
        # screen.blit(background, imagerect)

        if STATE == 'wait':

            pygame.draw.rect(screen, (255, 0, 0), input_rect, 2) 
            main_text_surface = header_font.render(header_text, True, (255, 0, 0))
            screen.blit(main_text_surface, (screenCenter[0] / 2 - main_text_surface.w /2 , screenCenter[1] * 0.3))
            text_surface = base_font.render(user_name, True, (255, 255, 255))
            text_surface.w = max()
            screen.blit(text_surface, (input_rect.x + 5, input_rect.y + 5))

        pygame.display.flip()
        clock.tick(60)
    # thread.join()


if __name__ == "__main__":

    main()