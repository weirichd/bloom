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

def hash_similarity(h1, h2):
    xord = h1 ^ h2
    ones = 0                    # lines like this make me laugh a little
    for i in range(32):
        if xord & 1 == 1:
            ones += 1
        xord = xord >> 1

    return float(ones) / 32.0

def flip_first_bit(string):
    ch = ord(string[0])
    first_bit = ch & 1
    new_ch = (ch & 0xFE) + ((first_bit + 1) % 2)

    return chr(new_ch) + string[1:]

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

    def test_changing_one_bit_on_average_changes_every_bit_with_probability_one_half(self):
        similarities = []
        for string in random_strings:
            for hash_number in range(20):
                h1 = pybloom.hash(hash_number, string)
                h2 = pybloom.hash(hash_number, flip_first_bit(string))
                similarities.append(hash_similarity(h1, h2))


        average = sum(similarities) / len(similarities)

        self.assertGreaterEqual(average, 0.4)
        self.assertLessEqual(average, 0.6)

if __name__ == '__main__':
    unittest.main()
