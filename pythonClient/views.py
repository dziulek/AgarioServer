import random
import arcade
from client import myInfo, game
from gameState import Player, GameState, MyInfo
import numpy as np

# --- Constants ---
SPRITE_SCALING_PLAYER = 0.5
SPRITE_SCALING_COIN = .25
COIN_COUNT = 50

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
SCREEN_TITLE = "Agar.io"


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



    def on_draw(self):
        """ Draw everything """
        arcade.start_render()
        # # draw players
        if game.players is not None:
            for player in game.players:
                for x, y, radius in player.coordinates:
                    arcade.draw_circle_filled(x, y, radius, arcade.color.RED)
                    arcade.draw_text(player.nickname, 
                            x, y, arcade.color.BLACK, 12, width=200, align="center", font_name='arial',
                                                   bold=True, anchor_x="center", anchor_y="center")
        
        # draw minis
        # for mini in game.map['minis']:

        # draw bombs
        # Put the text on the screen.
        # start_y = 250
        # start_x = 300
        # arcade.draw_point(start_x, start_y, arcade.color.BLUE, 5)
        # arcade.draw_text("Text centered on\na point",
        #                  start_x, start_y, arcade.color.BLACK, 14, width=200, align="center",
        #                  anchor_x="center", anchor_y="center")

    def on_mouse_motion(self, x, y, dx, dy):
        """ Handle Mouse Motion """
        global myInfo
        myInfo.addMousePosition([x, y])

    def on_update(self, delta_time):
        """ Movement and game logic """

    def on_key_press(self, key, modifiers):
        """Called whenever a key is pressed. """
        global myInfo

        if key == arcade.key.W:
            myInfo.addWAction()
        elif key == arcade.key.SPACE:
            myInfo.addDivideAction()

        


def main():
    """ Main method """

    player = Player()
    player.addCoordinate([100, 200, 20,400, 100, 50])
    player.coordinates = np.reshape(player.coordinates, (2, 3))
    player.addNickname('dziulek')
    game.appendPlayer(player)

    window = arcade.Window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    start_view = InstructionView()
    window.show_view(start_view)
    arcade.run()


if __name__ == "__main__":
    main()