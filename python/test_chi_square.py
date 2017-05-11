import sys
import unittest
import pybloom
import utils

with open("words.txt") as f:
    english_words = f.readlines()

with open("random_strings.txt") as f:
    random_strings = f.readlines()

class ChiSquareTest(unittest.TestCase):

    def test_given_english_hash_functions_individually_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        for hash_number in range(20):
            arr = utils.get_hashes(english_words, [hash_number])
            chi2, p = utils.calculate_p_value(arr)

            self.assertGreaterEqual(p, 0.05)

    def test_given_random_strings_hash_functions_individually_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        for hash_number in range(20):
            arr = utils.get_hashes(random_strings, [hash_number])
            chi2, p = utils.calculate_p_value(arr)

            self.assertGreaterEqual(p, 0.05)

    def test_given_english_and_random_strings_hash_functions_individually_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        for hash_number in range(20):
            arr = utils.get_hashes(english_words + random_strings, [hash_number])
            chi2, p = utils.calculate_p_value(arr)

            self.assertGreaterEqual(p, 0.05)

    def test_given_english_hash_functions_collectively_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        arr = utils.get_hashes(english_words, range(20))
        chi2, p = utils.calculate_p_value(arr)

        self.assertGreaterEqual(p, 0.05)

    def test_given_random_strings_hash_functions_collectively_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        arr = utils.get_hashes(random_strings, range(20))
        chi2, p = utils.calculate_p_value(arr)

        self.assertGreaterEqual(p, 0.05)

    def test_given_english_and_random_strings_hash_functions_collectively_pass_chi_square_test_with_P_value_greater_than_point_0_5(self):
        arr = utils.get_hashes(english_words + random_strings, range(20))
        chi2, p = utils.calculate_p_value(arr)

        self.assertGreaterEqual(p, 0.05)

if __name__ == '__main__':
    unittest.main()
