import unittest
import sys

sys.path.insert(1, '../..')
import numpy as np
from pythonClient.parseData import parse

class ParseTest(unittest.TestCase):

    def test_parse_data(self):
        
        buf["type"] = "data"
        #to do
        self.assertEqual(True, True)


if __name__ == "__main__":
    unittest.main()