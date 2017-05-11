import sys

import pybloom
import matplotlib.pyplot as plt
# import pylab
import numpy as np
import scipy.stats
import utils

fig = plt.figure()

def make_subplot(plot_title, file_path, position):
    with open(file_path) as f:
        words = f.readlines()

    arr = utils.get_hashes(words, [0])
    chi2, p = utils.calculate_p_value(arr)

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


make_subplot('235,886 English Words', 'words.txt', 211)
make_subplot('29,000 Random Strings', 'random_strings.txt', 212)

plt.tight_layout()

plt.show()
