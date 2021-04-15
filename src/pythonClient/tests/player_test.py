import unittest
import sys
import numpy as np

sys.path.insert(1, '../..')
from pythonClient.gameState import Player, GameState, MyInfo

class PlayerTest(unittest.TestCase):
    def test_get_set(self):
            player = Player()
            self.assertEqual(player.nickname, 'Unnamed_cell')

            player.addNickname('test')
            self.assertEqual(player.nickname, 'test')

            example = [[1,2],[2,3],[3,4]]
            player.setBlobsCoordinates(example)
            self.assertEqual(example, player.coordinates)
            
            player.clear()
            self.assertEqual(player.nickname, 'Unnamed_cell')
            self.assertEqual(np.shape(player.coordinates), (0,))
            self.assertEqual(player.color, 0xffffffff)

    def test_add_cordinate(self):
        player = Player()
        coord = np.array([1,1])
        player.addCoordinate(coord)
        print(player.coordinates)
        self.assertEqual(player.coordinates[0], 1)
        self.assertEqual(player.coordinates[1], 1)

if __name__ == '__main__':
    unittest.main()