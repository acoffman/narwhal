#ifndef BLOOM_H
#define BLOOM_H

#include <algorithm>
#include <string>
#include <cmath>
#include <limits.h>

using namespace std;

//thanks comp.lang.c!
#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

class BloomFilter {
  public:
    BloomFilter(int init_size);
    ~BloomFilter();
    void add(string item);
    bool include(string item);

  private:
    char * bitarray;
    int size;
    int djbHash(string item);
    int* keys(string item);

};
#include "bloomfilter.cpp"
#endif

