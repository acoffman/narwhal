#include "bloomfilter.h"
#include <iostream>

using namespace std;

int main(void){
  BloomFilter filter(1000);
  filter.add("hello");
  filter.add("oh!...oh!OH!");
  filter.add("anelfandhisham");
  filter.add("hello");
  filter.add("hi");
  filter.add("welcome");
  filter.add("y helo thar");
  filter.add("i hope this works");
  
  cout << filter.include("hello") << endl << filter.include("anelfandhisham") << endl << filter.include("abcde") << endl;
}
