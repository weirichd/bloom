[![Build Status](https://travis-ci.org/weirichd/bloom.svg?branch=master)](https://travis-ci.org/weirichd/bloom)

# bloom
Implementation of the code kata http://codekata.com/kata/kata05-bloom-filters/

## To build and run the tests
Run the command `make && make run_tests` from the root directory.

# Implementation Notes and Thoughts

This kata poses several interesting challenges. Here I log some of the thinking that went into specific implementation decisions.

## The Bit Field

The first component I decided to implement was the bit field. We need the ability to set bits in some portion of memory and then check to see if those bits were set. We have to make a choice for what we mean by "the 3rd bit" in the field. I initially decided that within a byte, bits would be counted from right to left, (i.e. least significant to most significant), and then bytes would be counted in memory order. So a 3 byte bit field would be counted as

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

We need a collection of hash functions which will map strings (`const char *`) to integers (`uint32_t`). For starters our basic requirements will be
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

## Should we write deterministic tests for the existence of false positives?

This seemed like an interesting question and I have seen implementation of the Bloom filter which did this. I decided to not write this kind of test however, because
* It would require engineering collisions, which, while not the most complicated thing in the world, would at least take a little effort
* The test would need to be rewritten every time the has function implementation changed.

These complications could be avoided by mocking the hash functions, but at that point what are you even testing which isn't already under test?
