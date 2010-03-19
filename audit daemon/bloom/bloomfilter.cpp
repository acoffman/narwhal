int BloomFilter::djbHash(string item){
	 int hash = 5381;
   for(int i = 0; i < item.length(); i++)
      hash = ((hash << 5) + hash) + item[i];
   return hash;
};

BloomFilter::BloomFilter(int init_size){
  size = init_size;
  bitarray = new char[BITNSLOTS(1000)];

};

BloomFilter::~BloomFilter(){
  delete []  bitarray;
};

void BloomFilter::add(string item){
  int * keys = this->keys(item);
	BITSET(bitarray, abs(keys[0]));
	BITSET(bitarray, abs(keys[1]));
	BITSET(bitarray, abs(keys[2]));
  delete [] keys;
};

bool BloomFilter::include(string item){
  int * keys = this->keys(item);
  bool result = (BITTEST(bitarray, keys[0]) && BITTEST(bitarray, keys[1]) && BITTEST(bitarray, keys[2]));
  delete [] keys;
  return result;
};

int * BloomFilter::keys(string item){
  int * keys = new int[3]; 
  string item1 = item;
  reverse(item1.begin(), item1.end());
  keys[0] = abs(djbHash(item) % size);
  keys[1] = abs(djbHash(item1) % size);
  keys[2] = abs(djbHash(item + item1) % size);
  return keys;
};
