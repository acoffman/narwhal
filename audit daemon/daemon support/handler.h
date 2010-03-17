#ifndef HANDLER_H
#define HANDLER_H


using namespace std;

class NotificationHandler {
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
#include "handler.cpp"
#endif


