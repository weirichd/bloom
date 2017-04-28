[![Build Status](https://travis-ci.org/weirichd/bloom.svg?branch=master)](https://travis-ci.org/weirichd/bloom)

# bloom
Implementation of the code kata http://codekata.com/kata/kata05-bloom-filters/

## To build and run the tests
Run the command `make && make run_tests` from the root directory.

# Implementation Notes and Thoughts

This kata poses several interesting challanges. Here I log some of the thinking that went into specific implementation decisions.

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
