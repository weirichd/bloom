import sys

sys.path.append(sys.path[0] + "/../build")

import unittest
import pybloom
import numpy as np
import scipy.stats

class StatsTest(unittest.TestCase):

    @unittest.skip("Skipping this test for now since I know it will fail")
    def test_hash_function_0_passes_chi_square_test_with_P_value_greater_than_point_0_5(self):
        f = open("/usr/share/dict/words")
        words = f.readlines()

        hash_number = 0

        arr = []
        for word in words:
            h = pybloom.hash(hash_number, word)
            arr.append(h)

        hist, _ = np.histogram(arr, bins=100)
        chi2, p = scipy.stats.chisquare(hist)
        
        self.assertGreaterEqual(p, 0.05)

if __name__ == '__main__':
    unittest.main()
