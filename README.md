[![Build Status](https://travis-ci.org/weirichd/bloom.svg?branch=master)](https://travis-ci.org/weirichd/bloom)

# bloom
Implementation of the code kata http://codekata.com/kata/kata05-bloom-filters/

## To build and run the tests
In the root directory, build a Docker image with the command

`docker build -t bloom_filter .`

To build and run C tests, use the command
`docker run -v $PWD:/src/app -w=/src/app bloom_filter /bin/bash -c 'make && make mem_test'`

To run Python (statistics) tests, run the command

`docker run -v $PWD:/src/app -w=/src/app bloom_filter /bin/bash -c 'cd python && python stats_test.py'`

On Linux or Mac, you can use the provided convenience script docker_test_script.sh to execute these two commands in order.

### Non-docker instructions

Alternatively, you can run outside a docker if you prefer. You will need installed the following requirements:
* gcc compatible compiler
* libcheck (I used version 0.11.0. At the time of this writing if you run `apt-get install libcheck` it will install version 0.10.0. That may or may not work.)
* Python 2.7
* numpy
* scipy
* Optional: matplotlib for generating plots.

Run the command `make && make run_tests` to build and test the C library.
Run `python python/stats_test.py` to run the statistics tests.

## Random Strings

Random strings provided by www.random.org

# Implementation Notes and Thoughts

This kata poses several interesting challenges.
Here I log some of the thinking that went into specific implementation decisions.

## The Bit Field

The first component I decided to implement was the bit field.
We need the ability to set bits in some portion of memory and then check to see if those bits were set.
We have to make a choice for what we mean by "the 3rd bit" in the field.
I initially decided that within a byte, bits would be counted from right to left, (i.e. least significant to most significant), and then bytes would be counted in memory order.
So a 3 byte bit field would be counted as

<table>
  <tr>
    <td colspan="8">Byte 0</td>
    <td colspan="8">Byte 1</td>
    <td colspan="8">Byte 2</td>
  </tr>
  <tr>
    <td>7</td> <td>6</td> <td>5</td> <td>4</td> <td>3</td> <td>2</td> <td>1</td> <td>0</td>
    <td>15</td> <td>14</td> <td>13</td> <td>12</td> <td>11</td> <td>10</td> <td>9</td> <td>8</td>
    <td>23</td> <td>22</td> <td>21</td> <td>20</td> <td>19</td> <td>18</td> <td>17</td> <td>16</td>
  </tr>
</table>

In order to force good memory alignment, I later switched to a `uint64_t` array instead of a `char` array, but used the same basic idea.

### Number of bits

I decided to use 32 bit addresses for the bit field. This allows up to ~4 billion bits in the field. A Bloom filter of this size could contain approx 270 million entries with a 0.1% false positive rate.

## Hash Functions

We need a collection of hash functions which will map strings (`const char *`) to integers (`uint32_t`).
For starters our basic requirements will be
* The same hash function has different results for different strings (`hash(i, str1) != hash(i str2)`)
* Different hash functions have different results for same strings (`hash(i, str) != hash(j, str)`).

Of course, the hash functions will a necessarily have collisions, but we'll ignore this complication for the moment.

### The "Dumb" Hash

As a first pass, I used the hash function

```c
uint32_t hash(int function_number, const char *str) {
    uint32_t h1 = 0;
    uint32_t h2 = 0;

    while(*str) {
        h1 += *str;
        h2 ^= *str;

        str++;
    }

    return h1 + h2*function_number;
}
```

This collection of functions is **awful**, in that it does not satisfy the needs of a "good" hash function, but for the purposes of getting the basic Bloom filter up and running this will suffice.

### A need to slightly improve
While writing a test which enforced the behavior that long words (in this case, 30 letters) could be read from the dictionary file I encountered some bad behavior.
The test loads the dictionary, and then checks that the word can be found.
Surprisingly, without even adding the word to the dictionary file the test passed right away *even though it should have failed.*
I suspected this was being caused by a false positive, so I wrote another test which adds a word, and then checks to see if a very similar word is **not** in the dictionary.
This second test failed, confirming my suspicions.
Decreasing the false positive rate of the filter had no effect, leading me to the conclusion that the dumb collection of hash functions were the culprit.
I altered the hash function collection slightly to a second iteration:

```c
const int a_big_prime_number = 0x0600BC09;

uint32_t hash(int function_number, const char *str) {
    uint32_t h1 = 0;
    uint32_t h2 = a_big_prime_number;

    while(*str) {
        h1 += *str;
        h2 ^= *str << 5;

        str++;
    }

    return h1 + h2*function_number;
}
```

I hadn't anticipated that I would need to alter the hash functions until I had reached the performance testing stage of development.
After all, even though the functions were pretty bad I assumed I would avoid collisions well enough in small early tests.
Yet, interestingly enough, a rather simple test forced this change.
This illustrates how important having "good" uniform hash functions are to the false positive rate of the Bloom filter.
After changing the hash function in this way, my similar word test passed and the long word test failed, which is the behavior I expected in the first place.

## Should we write deterministic tests for the existence of false positives?

This seemed like an interesting question and I have seen implementation of the Bloom filter which did this. I decided to not write this kind of test however, because
* It would require engineering collisions, which, while not the most complicated thing in the world, would at least take a little effort
* The test would need to be rewritten every time the has function implementation changed.

These complications could be avoided by mocking the hash functions, but at that point what are you even testing which isn't already under test?

# Profiling and Performance

With the core Bloom filter implemented, we are ready to start profiling.
When creating a filter of a particular capacity and false positive rate, we assume that our hash functions are sufficiently uniform.
We would like to verify this assumption.
We also want to confirm that we are actually attaining the desired false positive rate (or lower).

To do this, I decided to create Python wrappers for the Bloom library.
I could then leverage all of Python's excellent math and graphing capabilities.
While a more robust Python binding might be desired, I kept this to the bare minimum for what was required for me to do the needed profiling.

## First Profile

We want our hash functions to be uniform. So how do they stack up?
Below is a histogram of the frequency of the hashes of words in `/usr/share/dict/words`, a file which on my machine contains 235886 words.

![hashplot1](https://cloud.githubusercontent.com/assets/8379521/25866069/2e30d6da-34c3-11e7-8035-cb61ccc3d643.png)

Obviously there is room for improvement!

## One-at-a-time Hash

The third iteration of the hash function looks like this:

```
/* Bob Jenkins's One-at-a-time hash function source:
 *     https://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time
 *     http://www.burtleburtle.net/bob/hash/doobs.html
 */
uint32_t hash(int function_number, const char *str) {
    uint32_t h1 = 0;
    uint32_t h2 = a_big_prime_number;

    while(*str) {
        h1 += *str;
        h1 += h1 << 10;
        h1 ^= h1 >> 6;

        h2 ^= *str << 5;

        str++;
    }
    h1 += h1 << 3;
    h1 ^= h1 >> 11;
    h1 += h1 << 15;

    return h1 + h2 *(function_number + 1);
}
```

Here I incorporated the One-at-a-time hash written by Bob Jenkins for the `h1` component and removed the bad "addition hash." I also enforced that `h2` is always incorporated, even when `function_number = 0`.

![hashplot2](https://cloud.githubusercontent.com/assets/8379521/25873273/dc8c7348-34db-11e7-9af1-1727f95affb1.png)

As we can see, uniformity has improved tremendously!
