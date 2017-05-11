import sys
import unittest
import pybloom
import utils
import numpy as np
import scipy.stats

with open("random_strings.txt") as f:
    random_strings = f.readlines()

def shuffle(string):
    firstpart, secondpart = string[:len(string)/2], string[len(string)/2:]
    firstpart = firstpart[::-1]

    result = "".join(i + j for i, j in zip(firstpart, secondpart))

    if len(secondpart) != len(firstpart):
        result = result + secondpart[-1]

    return result

class HashStressTest(unittest.TestCase):

    def test_permuting_strings_gives_different_hashes(self):
        collisions = 0

        for string in random_strings:
            for hash_number in range(20):
                h1 = pybloom.hash(hash_number, string)
                h2 = pybloom.hash(hash_number, shuffle(string))

                if h1 == h2:
                    collisions += 1

        self.assertEqual(collisions, 0)

    def test_adding_one_character_gives_different_hashes(self):
        collisions = 0

        for string in random_strings:
            for hash_number in range(20):
                h1 = pybloom.hash(hash_number, string)
                h2 = pybloom.hash(hash_number, string + ' ')

                if h1 == h2:
                    collisions += 1

        self.assertEqual(collisions, 0)

if __name__ == '__main__':
    unittest.main()
