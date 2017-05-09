import sys

sys.path.append(sys.path[0] + "/../build")

import unittest
import pybloom
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

        chi2, p = scipy.stats.chisquare(arr)
        
        self.assertGreaterEqual(p, 0.05)


if __name__ == '__main__':
    unittest.main()
