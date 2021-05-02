import random
import arcade
import json
import sys
import math
from arcade.gui import UIManager
from arcade.gui.ui_style import UIStyle

from client import myInfo, game, myInfo_lock, game_lock, closeClient, connectToServer, listenOnSocket, writeToServerRoutine
from gameState import Player, GameState, MyInfo
from parseData import parse, fillMyData
import numpy as np
import copy
import time
import socket
import sys

ping = None
logic_time = None
drawing_time = None

BOMB_SPRITE_SIZE = 100

frames_per_second = 0
second = time.time()


SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800
SCREEN_TITLE = "Agar.io"

GRID_WIDTH = 10

colors = [
    arcade.color.AFRICAN_VIOLET,
    arcade.color.AIR_FORCE_BLUE,
    arcade.color.ALABAMA_CRIMSON,
    arcade.color.RED,
    arcade.color.YELLOW,
    arcade.color.PURPLE,
    arcade.color.VIOLET,
    arcade.color.BLUE,
    arcade.color.GREEN,
    arcade.color.MAGENTA,
    arcade.color.MANGO_TANGO,
    arcade.color.BLACK,
    arcade.color.MAROON,
    arcade.color.GRAY,
    arcade.color.BROWN,
    arcade.color.BUFF,
    arcade.color.ORANGE
]

def getColorFromInt(color):

    rgba = []

    rgba.append(color & 0xff)
    rgba.append(color >> 8 & 0xff)
    rgba.append(color >> 16 & 0xff)
    rgba.append(color >> 24 & 0xff)
    rgba.reverse()

    return rgba

def mapWindowCoordToView(x, y, view):

    height, width = view.window.get_size()

    view_x = x / width * (view.view_right - view.view_left) + view.view_left
    view_y = y / height * (view.view_top - view.view_bottom) + view.view_bottom

    view_x = int(view_x * 100) / 100
    view_y = int(view_y * 100) / 100

    return view_x, view_y


class PlayButton(arcade.gui.UIImageButton):

    def __init__(self, center_x, center_y, normal_texture, hover_texture, press_texture, text):
        super().__init__(
            center_x=center_x, 
            center_y=center_y, 
            normal_texture=normal_texture, 
            hover_texture=normal_texture, 
            press_texture=press_texture, 
            text=text,
            id='playbutton'
        )

        self.socket = None

        self.connection = None
        self.socket = None
        
    def on_click(self):
        
        self.connection = None
        try:
            self.socket = connectToServer()
            self.connection = True
        except ConnectionRefusedError:
            self.connection = False
        except socket.gaierror:
            self.connection = False

# class SpectateButton(arcade.gui.UIImageButton):


class InstructionView(arcade.View):

    def __init__(self):
        super().__init__()

        self.ui_manager = UIManager()

        self.socket = None

        self.connectionRefused = None
        self.brokenPipe = None
        self.rectangle = None

        self.ui_input_box = None

    def setup(self):

        self.ui_manager.purge_ui_elements()

        ui_input_box = arcade.gui.UIInputBox(
            center_x=SCREEN_WIDTH // 2,
            center_y=SCREEN_HEIGHT // 2 - 50,
            width=300,
            id='inputbox'
        )
        ui_input_box.text = 'unnamed cell'
        ui_input_box.cursor_index = len(ui_input_box.text)
        self.ui_manager.add_ui_element(ui_input_box)

        button_normal = arcade.load_texture(':resources:gui_basic_assets/red_button_normal.png')
        hovered_texture = arcade.load_texture(':resources:gui_basic_assets/red_button_hover.png')
        pressed_texture = arcade.load_texture(':resources:gui_basic_assets/red_button_press.png')
        button = PlayButton(
            center_x=SCREEN_WIDTH // 2,
            center_y=SCREEN_HEIGHT // 2 - 100,
            normal_texture=button_normal,
            hover_texture=hovered_texture,
            press_texture=pressed_texture,
            text='Play'
        )
        self.ui_manager.add_ui_element(button)

    def on_show(self):

        self.setup()
        arcade.set_background_color(arcade.csscolor.DARK_SLATE_BLUE)

        # Reset the viewport, necessary if we have a scrolling game and we need
        # to reset the viewport back to the start so we can see what we draw.
        arcade.set_viewport(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1)

    def on_hide_view(self):
        
        self.ui_manager.purge_ui_elements()

    def on_draw(self):
        """ Draw this view """
        arcade.start_render()
        
        if self.ui_input_box is not None:
            self.ui_input_box.draw()

        if self.rectangle is not None:
            self.rectangle.draw()

        arcade.draw_text("AGAR.IO", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
                         arcade.color.WHITE, font_size=50, anchor_x="center")

        if self.connectionRefused is not None:
            arcade.draw_text(self.connectionRefused, 0, 5, arcade.color.WHITE, 16, SCREEN_WIDTH, 'left', 'arial', bold=True, anchor_x='left', anchor_y='bottom')

    def on_update(self, delta_time):
        
        nickname = self.ui_manager.find_by_id('inputbox').text
        button = self.ui_manager.find_by_id('playbutton')
        if button is not None:
            if button.connection is not None:
                if button.connection is True:
                    try:
                        temp = {}
                        temp['nickname'] = nickname
                        temp['type'] = "want_play"
                        button.socket.send(bytearray(json.dumps(temp), 'utf-8'))
                        #czekamy na dane które ptrzebne są tylko raz, w tym przypadku tylko wysokość i szerokośc mapy
                        confirmation = button.socket.recv(100)
                        data = confirmation.decode()
                        if(int(data[:10]) == len(data)):
                            data = json.loads(data[10:])
                            width, height = data["map"]["width"], data["map"]["height"]
                        
                            game_view = GameView(float(width), float(height))
                            game_view.setup(button.socket)
                            self.window.show_view(game_view)      
     
                    except BrokenPipeError:
                        self.brokenPipe = True
                else:
                    self.rectangle = arcade.create_rectangle_filled(SCREEN_WIDTH // 2 - 135, 20, SCREEN_WIDTH * 3.4 / 5, 50, arcade.color.RED)
                    self.connectionRefused = 'Cannot connect to server,\ncheck your network connection and try again.'

    def on_mouse_press(self, _x, _y, _button, _modifiers):
        """ If the user presses the mouse button, start the game. """




class GameView(arcade.View):
    """ Our custom Window Class"""

    def __init__(self, map_width, map_height):
        """ Initializer """
        # Call the parent class initializer
        super().__init__()
        self.player_shapes = None
        self.mini_shapes = None
        self.players_nicks = None
        self.bombs_shapes = None
        self.abandoned_shapes = None

        self.map_rectangle = None

        self.map_width = map_width
        self.map_height = map_height

        self.view_left = 0
        self.view_right = SCREEN_WIDTH - 1
        self.view_bottom = 0
        self.view_top = SCREEN_HEIGHT - 1

        self.hor_points = None
        self.ver_points = None
        self.cursor_x = 0
        self.cursor_y = 0

        self.jsonObj = None

        self.window.set_mouse_visible(True)

        arcade.set_background_color(arcade.color.BABY_BLUE_EYES)

    def setup(self, s):
        """ Set up the game and initialize the variables. """
        
        self.socket = s

        img_bomb = "test.png"

        self.player_shapes = arcade.ShapeElementList()
        self.mini_shapes = arcade.ShapeElementList()
        self.bombs_shapes = arcade.SpriteList()
        self.abandoned_shapes = arcade.ShapeElementList()
        self.map_rectangle = arcade.create_rectangle_filled(
            SCREEN_WIDTH//2, SCREEN_HEIGHT//2, 
            SCREEN_WIDTH, SCREEN_HEIGHT, arcade.color.BISQUE)

        self.hor_points = np.array([])
        self.ver_points = np.array([])

    def on_draw(self):
        """ Draw everything """
        global drawing_time

        arcade.start_render()

        drawing_time = time.time()
        self.map_rectangle.draw()
        
        
        arcade.draw_lines(self.hor_points, arcade.color.WHITE_SMOKE, 0.25)
        arcade.draw_lines(self.ver_points, arcade.color.WHITE_SMOKE, 0.25)
        self.mini_shapes.draw()
        self.player_shapes.draw()
        self.bombs_shapes.draw()
        self.abandoned_shapes.draw()

        drawing_time = time.time() - drawing_time
        # draw bombs

    def on_mouse_motion(self, x, y, dx, dy):
        """ Handle Mouse Motion """
        self.cursor_x = int(x * 100) / 100
        self.cursor_y = int(y * 100) / 100

    def on_update(self, delta_time):
        """ Movement and game logic """
        global ping, logic_time, second, frames_per_second

        if self.jsonObj is not None and bool(int(chr(self.jsonObj["you"]["state"]))) == False:
            #lost game
            self.socket.close()
            game_over = GameOverView("YOU LOST")
            self.window.show_view(game_over)
        
        else:

            logic_time = time.time()
            self.map_rectangle = arcade.create_rectangle_filled(
                self.map_width // 2, self.map_height//2,
                self.map_width, self.map_height,
                arcade.color.EUCALYPTUS
            )

            self.player_shapes = arcade.ShapeElementList()
            self.players_nicks = []
            if self.jsonObj is not None:
                for player in self.jsonObj["players"]:
                    for x, y, radius in zip(
                        self.jsonObj["players"][player]["blobs"]["x"], 
                        self.jsonObj["players"][player]["blobs"]["y"], 
                        self.jsonObj["players"][player]["blobs"]["radius"]
                    ):
                        shape = arcade.create_ellipse_filled(x * 0.01, y * 0.01, 2 * radius * 0.01, 2 * radius * 0.01, getColorFromInt(self.jsonObj["players"][player]["color"]))
                        self.player_shapes.append(shape)

            if self.jsonObj is not None:
                self.mini_shapes = arcade.ShapeElementList()
                for x, y, color in zip(
                    self.jsonObj["map"]["minis"]["x"],
                    self.jsonObj["map"]["minis"]["y"],
                    self.jsonObj["map"]["minis_color"]
                ):
                    radius = self.jsonObj["map"]["minis"]["radius"]
                    shape = arcade.create_ellipse_filled(x, y, 2 * radius, 2 * radius, getColorFromInt(color))
                    self.mini_shapes.append(shape)

            if self.jsonObj is not None:
                self.abandoned_shapes = arcade.ShapeElementList()
                for x, y, radius, color in zip(
                    self.jsonObj["map"]["abandoned"]["x"],
                    self.jsonObj["map"]["abandoned"]["y"],
                    self.jsonObj["map"]["abandoned"]["radius"],
                    self.jsonObj["map"]["abandoned"]["colors"]
                ):
                    shape = arcade.create_ellipse_filled(x * 0.01, y * 0.01, 2 * radius * 0.01, 2 * radius * 0.01, getColorFromInt(color))
                    self.abandoned_shapes.append(shape)

            if self.jsonObj is not None:
                self.bombs_shapes = arcade.SpriteList()
                for x, y in zip(
                    self.jsonObj["map"]["bombs"]["x"],
                    self.jsonObj["map"]["bombs"]["y"]
                ):
                    radius = self.jsonObj["map"]["bombs"]["radius"]
                    shape = arcade.Sprite("bombv3.png",  radius / BOMB_SPRITE_SIZE)
                    shape.center_x = x
                    shape.center_y = y
                    self.bombs_shapes.append(shape)

            if self.jsonObj is not None:  
                self.view_left = copy.deepcopy(self.jsonObj["you"]["view"][0]) * 0.01
                self.view_right = copy.deepcopy(self.jsonObj["you"]["view"][2]) * 0.01
                self.view_bottom = copy.deepcopy(self.jsonObj["you"]["view"][1]) * 0.01
                self.view_top = copy.deepcopy(self.jsonObj["you"]["view"][3]) * 0.01


            arcade.set_viewport(self.view_left, self.view_right, self.view_bottom, self.view_top)

            left, right, bottom, top = self.view_left, self.view_right, self.view_bottom, self.view_top

            left = (left // GRID_WIDTH * GRID_WIDTH)
            right = (right + GRID_WIDTH) // GRID_WIDTH * GRID_WIDTH
            bottom = bottom // GRID_WIDTH * GRID_WIDTH
            top = (top + GRID_WIDTH) // GRID_WIDTH * GRID_WIDTH

            self.hor_points = np.zeros(int((top - bottom) // GRID_WIDTH) * 4 + 4)
            self.ver_points = np.zeros(int((right - left) // GRID_WIDTH) * 4 + 4)

            y_coord = bottom
            for i in range(len(self.hor_points) // 4):
                self.hor_points[4 * i] = left
                self.hor_points[4 * i + 2] = right
                self.hor_points[4 * i + 1] = y_coord
                self.hor_points[4 * i + 3] = y_coord

                y_coord += GRID_WIDTH

            x_coord = left
            for i in range(len(self.ver_points) // 4):
                self.ver_points[4 * i] = x_coord
                self.ver_points[4 * i + 1] = bottom
                self.ver_points[4 * i + 2] = x_coord
                self.ver_points[4 * i + 3] = top

                x_coord += GRID_WIDTH
            
            self.hor_points = np.reshape(self.hor_points, (len(self.hor_points) // 2, 2))
            self.ver_points = np.reshape(self.ver_points, (len(self.ver_points) // 2, 2))
            logic_time = time.time() - logic_time

            myInfo.addMousePosition(mapWindowCoordToView(self.cursor_x, self.cursor_y, self))
            ping = time.time()
            try: 
                writeToServerRoutine(self.socket)
            except BrokenPipeError:
                #broken pipe
                self.socket.close()
                game_over = GameOverView("UPS, LOST CONNECTION")
                self.window.show_view(game_over)
            try:
                self.jsonObj = listenOnSocket(self.socket)
                ping = time.time() - ping
                # print(json.dumps(self.jsonObj))
            except OSError:
                #bad file descriptor, inactive socket
                self.socket.close()
                game_over = GameOverView("UPS, LOST CONNECTION")
                self.window.show_view(game_over)
            print(
                'ping: ', "{:.6f}".format(ping), 
                ', logic: ', "{:.4f}".format(logic_time), 
                ', drawing: ', "{:.4f}".format(drawing_time), 
                'total: ', "{:.4f}".format(ping + logic_time + drawing_time)
            )

    def on_key_press(self, key, modifiers):
        """Called whenever a key is pressed. """
        global myInfo

        if key == arcade.key.W:
            myInfo.addWAction(True)
        elif key == arcade.key.SPACE:
            myInfo.addDivideAction(True)
        elif key == arcade.key.ESCAPE:
            self.socket.close()
            game_over = GameOverView("YOU QUIT THE GAME")
            self.window.show_view(game_over)


class GameOverView(arcade.View):
    """ View to show when game is over """

    def __init__(self, text):
        """ This is run once when we switch to this view """
        super().__init__()

        # Reset the viewport, necessary if we have a scrolling game and we need
        # to reset the viewport back to the start so we can see what we draw.
        arcade.set_viewport(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1)
        arcade.set_background_color(arcade.csscolor.DARK_SLATE_BLUE)

        self.text = text

    def on_draw(self):
        """ Draw this view """
        arcade.start_render()

        arcade.draw_text(self.text.upper(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
                         arcade.color.WHITE, font_size=50, anchor_x="center")
        arcade.draw_text("Click to play again", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-75,
                         arcade.color.WHITE, font_size=20, anchor_x="center")

    def on_mouse_press(self, _x, _y, _button, _modifiers):
        """ If the user presses the mouse button, re-start the game. """
        start_view = InstructionView()
        start_view.setup()
        self.window.show_view(start_view)

def main():
    """ Main method """

    if len(sys.argv) != 3:
        print("Uruchomienie klienta: python views.py <serwer ip> <numer portu>")
    
    else:
        window = arcade.Window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
        start_view = InstructionView()
        window.show_view(start_view)
        arcade.run()


if __name__ == "__main__":
    main()