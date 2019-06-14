# SubSetIterator

Subset Iteration can be quite useful when you want to brute force explore an entire powerset.
There are many ways to go about it which involve recursion as well.

This SubsetIterator was build using a gray code encoding scheme. This helps building the sets lazily.
And helps over iterating the standard binary encoding scheme by saving on allocations/ deallocations.

I was able to iterate over a power-set of 27 strings (avg. length of such strings: 4.7), which would have $2^{27} = 134,217,728$ subsets in ~1.5 seconds. [2015 MBP running a 2.7GHZ processor, g++-8] which corresponds to about ~11 nano seconds per iteration. The checksum of the sum of lengths of strings of a subset was used for testing.

## Build

```
g++ -o testF.o -O3 -std=c++11 test.C && time ./testF.o
```

To test the binary encoding scheme:

```
g++ -o test.o -O3 -std=c++11 -DTEST test.C && time ./test.o
```
