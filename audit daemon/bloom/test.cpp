#include "bloomfilter.h"
#include <iostream>

using namespace std;

int main(void){
  BloomFilter filter(1000);
  filter.add("hello");
  filter.add("oh!...oh!OH!");
  filter.add("anelfandhisham");
  
  cout << filter.include("hello") << endl << filter.include("anelfandhisham") << endl << filter.include("abcde") << endl;
}
