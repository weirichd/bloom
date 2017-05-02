import hash
import matplotlib.pyplot as plt

f = open("/usr/share/dict/words")

arr = []
for line in f:
    h = hash.hash(10, line)
    arr.append(h)

binsize = (max(arr) - min(arr)) / 100

plt.hist(arr, bins=range(min(arr), max(arr) + binsize, binsize))
plt.show()
