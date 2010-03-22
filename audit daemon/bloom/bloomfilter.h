#ifndef BLOOM_H
#define BLOOM_H

#include <algorithm>
#include <string>
#include <limits.h>
#include <iostream>

using namespace std;

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)
#define ABS(a) a > 0 ? a : a * -1 

class BloomFilter {
  public:
    BloomFilter(int init_size);
    ~BloomFilter();
    void add(string item);
    bool include(string item);
    char* getBitArray();
    int getSize();

  private:
    char * bitarray;
    int size;
    int djbHash(string item);
    int* keys(string item);
    char * ti_concat(const char * c1, const char * c2);

};
#include "bloomfilter.cpp"
#endif

