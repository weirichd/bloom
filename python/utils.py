import pybloom
import math
import numpy as np
import scipy.stats

def get_hashes(word_list, hash_numbers):
    hashes = []
    for hash_number in hash_numbers:
        for word in word_list:
            h = pybloom.hash(hash_number, word)
            hashes.append(h)

    return hashes

# Source for this formula: http://kb.palisade.com/index.php?pg=kb.page&id=57
# They in turn cite "Goodness-of-Fit Tests" by Ralph D'Agostino and Michael Stephens (Dekker 1986), page 70.
def number_of_bins(array):
    if len(array) < 35:
        return int(math.round(len(array) / 5.0))
    else:
        return int(1.88 * len(array)**(0.4))

def calculate_p_value(values):
    hist, _ = np.histogram(values, number_of_bins(values))
    normalization = float(number_of_bins(values)) / float(len(values))
    normalized_hist = [h * normalization for h in hist]

    return scipy.stats.chisquare(normalized_hist)
