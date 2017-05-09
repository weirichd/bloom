import sys

import pybloom
import matplotlib.pyplot as plt
# import pylab
import numpy as np
import scipy.stats

fig = plt.figure()

def make_subplot(plot_title, file_path, position):
    f = open(file_path)
    words = f.readlines()

    hash_number = 0

    arr = []
    for word in words:
        h = pybloom.hash(hash_number, word)
        arr.append(h)

    hist, _ = np.histogram(arr, bins=100)
    chi2, p = scipy.stats.chisquare(hist)

    binsize = (max(arr) - min(arr)) / 50

    ax = fig.add_subplot(position)
    ax.set_title(plot_title)
    ax.set_xlabel('Hash value')
    ax.set_ylabel('Bin frequency')

    caption = '$\chi^2 =$ {}\n$p = ${}'.format(chi2, p)

    ax.annotate(caption,
            xy=(.95, .9),
            xycoords='axes fraction',
            horizontalalignment='right',
            verticalalignment='top',
            style='italic',
            bbox={'facecolor':'red', 'alpha':0.5, 'pad':10})

    plt.hist(arr, bins=range(min(arr), max(arr) + binsize, binsize))


make_subplot('235,886 English Words', '/usr/share/dict/words', 211)
make_subplot('17,000 Random Strings', 'random_strings.txt', 212)

plt.tight_layout()

plt.show()
