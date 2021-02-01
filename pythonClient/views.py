import random
import arcade
from client import myInfo, game, myInfo_lock, game_lock, closeClient, connectToServer
from gameState import Player, GameState, MyInfo
import numpy as np


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

        # Variables that will hold sprite lists
        
        # Set up the player info

        # Don't show the mouse cursor
        self.window.set_mouse_visible(True)

        arcade.set_background_color(arcade.color.AMAZON)

    def setup(self):
        """ Set up the game and initialize the variables. """
        game = None
        connectToServer()


    def on_draw(self):
        """ Draw everything """
        global game
        
        game_lock.acquire()
        if len(game.view) == 4:
            arcade.set_viewport(game.view[0], game.view[2], game.view[1], game.view[3])

            # print('viewport: ', game.view[0], game.view[1], game.view[2], game.view[3])
        game_lock.release()

        arcade.start_render()
        
        left, right, bottom, top = arcade.get_viewport()

        left = (left // GRID_WIDTH * GRID_WIDTH)
        right = (right + GRID_WIDTH) // GRID_WIDTH * GRID_WIDTH
        bottom = bottom // GRID_WIDTH * GRID_WIDTH
        top = (top + GRID_WIDTH) // GRID_WIDTH * GRID_WIDTH

        hor_points = np.zeros(int((top - bottom) // GRID_WIDTH) * 4 + 4)
        ver_points = np.zeros(int((right - left) // GRID_WIDTH) * 4 + 4)

        y_coord = bottom
        for i in range(len(hor_points) // 4):
            hor_points[4 * i] = left
            hor_points[4 * i + 2] = right
            hor_points[4 * i + 1] = y_coord
            hor_points[4 * i + 3] = y_coord

            y_coord += GRID_WIDTH

        x_coord = left
        for i in range(len(ver_points) // 4):
            ver_points[4 * i] = x_coord
            ver_points[4 * i + 1] = bottom
            ver_points[4 * i + 2] = x_coord
            ver_points[4 * i + 3] = top

            x_coord += GRID_WIDTH
        
        hor_points = np.reshape(hor_points, (len(hor_points) // 2, 2))
        ver_points = np.reshape(ver_points, (len(ver_points) // 2, 2))

        arcade.draw_lines(hor_points, arcade.color.WHITE_SMOKE, 0.5)
        arcade.draw_lines(ver_points, arcade.color.WHITE_SMOKE, 0.5)

        # shape_list = arcade.create_isometric_grid_lines(50, 50, 7, 7, arcade.color.WHITE, 0.5)

        # for shape in shape_list:
        #     arcade.Shape.draw(shape)
        # # draw players
        game_lock.acquire()
        if game.players is not None:
            for player in game.players:
                for x, y, radius in player.coordinates:
                    arcade.draw_circle_filled(x, y, radius, arcade.color.REDWOOD)
                    # arcade.draw_text(player.nickname, 
                    #         x, y, arcade.color.BLACK, 12, width=200, align="center", font_name='arial',
                    #                                bold=True, anchor_x="center", anchor_y="center")
        game_lock.release()
    
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
        myInfo_lock.release()

    def on_update(self, delta_time):
        """ Movement and game logic """



    def on_key_press(self, key, modifiers):
        """Called whenever a key is pressed. """
        global myInfo

        if key == arcade.key.W:
            myInfo.addWAction()
        elif key == arcade.key.SPACE:
            myInfo.addDivideAction()
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