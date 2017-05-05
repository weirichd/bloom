import sys

sys.path.append(sys.path[0] + "/../build")

import pybloom
import matplotlib.pyplot as plt
import pylab

f = open("/usr/share/dict/words")

arr = []
for line in f:
    h = pybloom.hash(0, line)
    arr.append(h)

binsize = (max(arr) - min(arr)) / 50
plt.hist(arr, bins=range(min(arr), max(arr) + binsize, binsize))
pylab.savefig("hashplot.png")

pybloom.create(100, 0.01)
pybloom.put('David')

if pybloom.contains('Daivd'):
    print 'YES'
else:
    print 'no...'
