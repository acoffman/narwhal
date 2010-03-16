#ifndef AVL_H
#define AVL_H

#include <boost/dynamic_bitset.hpp>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

class BloomFilter {
  public:
    BloomFilter(int init_size);
    ~BloomFilter();
    void add(string item);
    bool include(string item);

  private:
    boost::dynamic_bitset<> * bitset;
    int size;
    int djbHash(string item);
    int* keys(string item);

};
#include "bloomfilter.cpp"
#endif

