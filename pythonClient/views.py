import random
import arcade
from arcade.gui import UIManager
from arcade.gui.ui_style import UIStyle
from client import myInfo, game, myInfo_lock, game_lock, closeClient, connectToServer, listenOnSocket, writeToServerRoutine
from gameState import Player, GameState, MyInfo
import numpy as np
import copy


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

    return rgba

def mapWindowCoordToView(x, y, view):

    height, width = view.window.get_size()

    view_x = x / width * (view.view_right - view.view_left) + view.view_left
    view_y = y / height * (view.view_top - view.view_bottom) + view.view_bottom

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

class InstructionView(arcade.View):

    def __init__(self):
        super().__init__()

        self.ui_manager = UIManager()

        self.socket = None

        self.connectionRefused = None
        self.rectangle = None

        self.ui_input_box = None

    def setup(self):

        self.ui_manager.purge_ui_elements()

        ui_input_box = arcade.gui.UIInputBox(
            center_x=SCREEN_WIDTH // 2,
            center_y=SCREEN_HEIGHT // 2 - 50,
            width=300
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
            arcade.draw_text(self.connectionRefused, 0, 5, arcade.color.WHITE, 16, SCREEN_WIDTH, 'left', 'calibri', bold=True, anchor_x='left', anchor_y='bottom')

    def on_update(self, delta_time):
        
        button = self.ui_manager.find_by_id('playbutton')
        if button is not None:
            if button.connection is not None:
                if button.connection is True:
                    game_view = GameView()
                    game_view.setup(button.socket)
                    self.window.show_view(game_view)
                else:
                    self.rectangle = arcade.create_rectangle_filled(SCREEN_WIDTH // 2 - 135, 20, SCREEN_WIDTH * 3.4 / 5, 50, arcade.color.RED)
                    self.connectionRefused = 'Cannot connect to server,\ncheck your network connection and try again.'

    def on_mouse_press(self, _x, _y, _button, _modifiers):
        """ If the user presses the mouse button, start the game. """




class GameView(arcade.View):
    """ Our custom Window Class"""

    def __init__(self):
        """ Initializer """
        # Call the parent class initializer
        super().__init__()
        self.player_shapes = None
        self.mini_shapes = None

        self.map_rectangle = None

        self.view_left = 0
        self.view_right = SCREEN_WIDTH - 1
        self.view_bottom = 0
        self.view_top = SCREEN_HEIGHT - 1

        self.hor_points = None
        self.ver_points = None

        self.window.set_mouse_visible(True)

        arcade.set_background_color(arcade.color.DARK_BLUE)

    def setup(self, s):
        """ Set up the game and initialize the variables. """
        
        self.socket = s

        self.socket.send(bytearray('get.game', 'utf-8'))
        listenOnSocket(self.socket)

        self.player_shapes = arcade.ShapeElementList()
        self.mini_shapes = arcade.ShapeElementList()
        self.map_rectangle = arcade.create_rectangle_filled(
            SCREEN_WIDTH//2, SCREEN_HEIGHT//2, 
            SCREEN_WIDTH, SCREEN_HEIGHT, arcade.color.AMAZON)

        self.hor_points = np.array([])
        self.ver_points = np.array([])


    def on_draw(self):
        """ Draw everything """
        arcade.start_render()

        self.map_rectangle.draw()
        self.player_shapes.draw()
        
        arcade.draw_lines(self.hor_points, arcade.color.WHITE_SMOKE, 0.25)
        arcade.draw_lines(self.ver_points, arcade.color.WHITE_SMOKE, 0.25)
        # draw minis
        self.mini_shapes.draw()

        # draw bombs

    def on_mouse_motion(self, x, y, dx, dy):
        """ Handle Mouse Motion """
        vx, vy = mapWindowCoordToView(x, y, self)

        global myInfo
        myInfo.addMousePosition([vx, vy])

    def on_update(self, delta_time):
        """ Movement and game logic """
        # global myInfo
        # vx, vy = mapWindowCoordToView(arcade.Window.get_system_mouse_cursor(), y, self)
        # myInfo.addMousePosition([vx, vy])

        
        self.socket.send(bytearray('get.game', 'utf-8'))
        listenOnSocket(self.socket)

        self.map_rectangle = arcade.create_rectangle_filled(
            game.map['width'] // 2, game.map['height']//2,
            game.map['width'], game.map['height'],
            arcade.color.AMAZON
        )

        self.player_shapes = arcade.ShapeElementList()
        if game.players is not None:
            for player in game.players:
                for x, y, radius in player.coordinates:
                    shape = arcade.create_ellipse_filled(x, y, 2 * radius, 2 * radius, arcade.color.WATERSPOUT)
                    self.player_shapes.append(shape)
        
        if game.map['minis'] is not None:
            self.mini_shapes = arcade.ShapeElementList()
            for mini, color in zip(game.map['minis'], game.map['colors']):
                x, y, radius = mini
                shape = arcade.create_ellipse_filled(x, y, 2 * radius, 2 * radius, getColorFromInt(color))
                self.mini_shapes.append(shape)

        if len(game.view) == 4:
            
            self.view_left = copy.deepcopy(game.view[0])
            self.view_right = copy.deepcopy(game.view[2])
            self.view_bottom = copy.deepcopy(game.view[1])
            self.view_top = copy.deepcopy(game.view[3])


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

        writeToServerRoutine(self.socket)


    def on_key_press(self, key, modifiers):
        """Called whenever a key is pressed. """
        global myInfo

        if key == arcade.key.W:
            myInfo.addWAction(1)
        elif key == arcade.key.SPACE:
            myInfo.addDivideAction(1)
        elif key == arcade.key.A:
            arcade.set_viewport(45, 145, 7, 34)
        elif key == arcade.key.ESCAPE:
            self.socket.close()
            game_over = GameOverView()
            self.window.show_view(game_over)


class GameOverView(arcade.View):
    """ View to show when game is over """

    def __init__(self):
        """ This is run once when we switch to this view """
        super().__init__()

        # Reset the viewport, necessary if we have a scrolling game and we need
        # to reset the viewport back to the start so we can see what we draw.
        arcade.set_viewport(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1)
        arcade.set_background_color(arcade.csscolor.DARK_SLATE_BLUE)

    def on_draw(self):
        """ Draw this view """
        arcade.start_render()

        arcade.draw_text("YOU QUIT THE GAME", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
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
    
    window = arcade.Window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    start_view = InstructionView()
    window.show_view(start_view)
    arcade.run()


if __name__ == "__main__":
    main()