import unittest
import sys
import numpy as np
sys.path.insert(1, '../..')

from pythonClient.gameState import GameState

class GameTest(unittest.TestCase):
    def test_set_view(self):
        game = GameState()
        view = [[0,0],[1,1]]
        game.setView(view)

        self.assertEqual(np.shape(view), np.shape(game.view))
        
if __name__ == "__main__":
    unittest.main()