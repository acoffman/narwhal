#include "bloomfilter.h"
#include <iostream>

using namespace std;

int main(void){
  BloomFilter filter(104);
  filter.add("hello");
  
  cout << filter.include("hello") << endl << filter.include("anelfandhisham") << endl << filter.include("abcde") << endl;
}
