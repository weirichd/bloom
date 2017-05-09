import sys

sys.path.append(sys.path[0] + "/../build")

import pybloom
import matplotlib.pyplot as plt
import pylab
import scipy.stats

f = open("/usr/share/dict/words")

words = f.readlines()

hash_number = 0

arr = []
for word in words:
    h = pybloom.hash(hash_number, word)
    arr.append(h)

chi2, p = scipy.stats.chisquare(arr)
caption = 'chi^2 = {}\np = {}'.format(chi2, p)

binsize = (max(arr) - min(arr)) / 50

fig = plt.figure()
plt.hist(arr, bins=range(min(arr), max(arr) + binsize, binsize))
fig.text(0.5, 0.5, caption)

pylab.savefig("plot.png")

print "Results:\n" + caption
