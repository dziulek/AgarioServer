import random
import arcade
from client import myInfo, game, myInfo_lock, game_lock, closeClient, connectToServer
from gameState import Player, GameState, MyInfo
import numpy as np
import copy


SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800
SCREEN_TITLE = "Agar.io"

GRID_WIDTH = 20


class InstructionView(arcade.View):

    def on_show(self):
        arcade.set_background_color(arcade.csscolor.DARK_SLATE_BLUE)

        # Reset the viewport, necessary if we have a scrolling game and we need
        # to reset the viewport back to the start so we can see what we draw.
        arcade.set_viewport(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1)

    def on_draw(self):
        """ Draw this view """
        arcade.start_render()
        arcade.draw_text("AGAR.IO", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
                         arcade.color.WHITE, font_size=50, anchor_x="center")
        arcade.draw_text("Click to play", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-75,
                         arcade.color.WHITE, font_size=20, anchor_x="center")

    def on_mouse_press(self, _x, _y, _button, _modifiers):
        """ If the user presses the mouse button, start the game. """
        game_view = GameView()
        game_view.setup()
        self.window.show_view(game_view)


class GameView(arcade.View):
    """ Our custom Window Class"""

    def __init__(self):
        """ Initializer """
        # Call the parent class initializer
        super().__init__()
        self.shape_list = None

        self.view_left = 0
        self.view_right = SCREEN_WIDTH - 1
        self.view_bottom = 0
        self.view_top = SCREEN_HEIGHT - 1

        self.hor_points = None
        self.ver_points = None

        self.window.set_mouse_visible(True)

        arcade.set_background_color(arcade.color.AMAZON)

    def setup(self):
        """ Set up the game and initialize the variables. """
        
        connectToServer()

        self.shape_list = arcade.ShapeElementList()
        self.hor_points = np.array([])
        self.ver_points = np.array([])


    def on_draw(self):
        """ Draw everything """
        arcade.start_render()

        # for shape in shape_list:
        #     arcade.Shape.draw(shape)
        # # draw players
        self.shape_list.draw()
    
        arcade.draw_lines(self.hor_points, arcade.color.WHITE_SMOKE, 0.5)
        arcade.draw_lines(self.ver_points, arcade.color.WHITE_SMOKE, 0.5)
        # draw minis
        # for mini in game.map['minis']:

        # draw bombs

    def on_mouse_motion(self, x, y, dx, dy):
        """ Handle Mouse Motion """
        width, height = arcade.Window.get_size(self.window)
        vx = x - width / 2.0
        vy = y - height / 2.0

        global myInfo
        myInfo_lock.acquire()
        myInfo.addMousePosition([vx, vy])
        # print(myInfo.attributes['mouse'][0], myInfo.attributes['mouse'][1])
        myInfo_lock.release()

    def on_update(self, delta_time):
        """ Movement and game logic """
        game_lock.acquire()
        self.shape_list = arcade.ShapeElementList()
        if game.players is not None:
            for player in game.players:
                for x, y, radius in player.coordinates:
                    arcade.draw_circle_filled(x, y, radius, arcade.color.REDWOOD)
                    shape = arcade.create_rectangle_filled(x, y, 10, 10, arcade.color.WATERSPOUT)
                    self.shape_list.append(shape)

        if len(game.view) == 4:
            
            self.view_left = copy.deepcopy(game.view[0])
            self.view_right = copy.deepcopy(game.view[2])
            self.view_bottom = copy.deepcopy(game.view[1])
            self.view_top = copy.deepcopy(game.view[3])
        game_lock.release()

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
            arcade.close_window()
            closeClient = True

def main():
    """ Main method """
    
    window = arcade.Window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    start_view = InstructionView()
    window.show_view(start_view)
    arcade.run()


if __name__ == "__main__":
    main()