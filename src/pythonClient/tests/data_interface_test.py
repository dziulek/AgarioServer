import unittest
import sys
import json

sys.path.insert(1, '../..')
import numpy as np
from pythonClient.parseData import parse
from pythonClient.gameState import GameState, MyInfo, Player

class ParseTest(unittest.TestCase):

    def test_parse_want_play(self):
        
        buf = {}
        buf["type"] = "want_play"
        buf["map"] = {}
        buf["map"]["height"] = 1000
        buf["map"]["width"] = 1000

        width, height = parse(json.dumps(buf), GameState())
        
        self.assertEqual(width, 1000)
        self.assertEqual(height, 1000)

    def test_parse_data(self):
        
        gameState = GameState()

        buf = """{"type":"data","map":{"abandoned":{"x":[],"y":[]},
        "bombs":{"x":[17],"y":[277]},
        "minis":{"x":[155],
        "y":[115]}},
        "players":{"0":{"blobs":{"x":[248],"y":[202]},
        "color":4294967295,"nickname":"foo"}},
        "you": {"state":49,"view":[189,143,
        307,261]}}"""

        parse(buf, gameState)
        self.assertEqual(gameState.map["minis"][0][0], 155)
        self.assertEqual(gameState.map["minis"][0][1], 115)
        self.assertEqual(len(gameState.players), 1)
        self.assertEqual(gameState.players[0].nickname, "foo")
        self.assertEqual(gameState.players[0].color, 4294967295)
        self.assertEqual(np.shape(gameState.view), (2,2))
        self.assertEqual(gameState.view[0][0], 189)
        self.assertEqual(gameState.view[1][1], 261)

        self.assertEqual(len(gameState.map["abandoned"]), 0)
        self.assertEqual(gameState.map["bombs"][0][0], 17)
        self.assertEqual(gameState.map["bombs"][0][1], 277)

        self.assertEqual(gameState.playerState, True)

if __name__ == "__main__":
    unittest.main()