import sys
import unittest
import pybloom
import numpy as np
import scipy.stats

with open("words.txt") as f:
    english_words = f.readlines()

with open("random_strings.txt") as f:
    random_strings = f.readlines()

class ChiSquareTest(unittest.TestCase):

    def test_given_english_hash_functions_individually_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        for hash_number in range(20):
            arr = []
            for word in english_words:
                h = pybloom.hash(hash_number, word)
                arr.append(h)

            hist, _ = np.histogram(arr, bins=100)
            chi2, p = scipy.stats.chisquare(hist)

            self.assertGreaterEqual(p, 0.05)

    def test_given_random_strings_hash_functions_individually_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        for hash_number in range(20):
            arr = []
            for word in random_strings:
                h = pybloom.hash(hash_number, word)
                arr.append(h)

            hist, _ = np.histogram(arr, bins=100)
            chi2, p = scipy.stats.chisquare(hist)

            self.assertGreaterEqual(p, 0.05)

    def test_given_english_and_random_strings_hash_functions_individually_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        for hash_number in range(20):
            arr = []
            for word in english_words + random_strings:
                h = pybloom.hash(hash_number, word)
                arr.append(h)

            hist, _ = np.histogram(arr, bins=100)
            chi2, p = scipy.stats.chisquare(hist)

            self.assertGreaterEqual(p, 0.05)

    def test_given_english_hash_functions_collectively_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        arr = []
        for hash_number in range(20):
            for word in english_words:
                h = pybloom.hash(hash_number, word)
                arr.append(h)

        hist, _ = np.histogram(arr, bins=100)
        chi2, p = scipy.stats.chisquare(hist)

        self.assertGreaterEqual(p, 0.05)

    def test_given_random_strings_hash_functions_collectively_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        arr = []
        for hash_number in range(20):
            for word in random_strings:
                h = pybloom.hash(hash_number, word)
                arr.append(h)

        hist, _ = np.histogram(arr, bins=100)
        chi2, p = scipy.stats.chisquare(hist)

        self.assertGreaterEqual(p, 0.05)

    def test_given_english_and_random_strings_hash_functions_collectively_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        arr = []
        for hash_number in range(20):
            for word in english_words + random_strings:
                h = pybloom.hash(hash_number, word)
                arr.append(h)

        hist, _ = np.histogram(arr, bins=100)
        chi2, p = scipy.stats.chisquare(hist)

        self.assertGreaterEqual(p, 0.05)

if __name__ == '__main__':
    unittest.main()
