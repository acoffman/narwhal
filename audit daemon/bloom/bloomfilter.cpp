int BloomFilter::djbHash(string item){
	 int hash = 5381;
   for(int i = 0; i < item.length(); i++)
      hash = ((hash << 5) + hash) + item[i];
   return hash;
};

BloomFilter::BloomFilter(int init_size){
  size = init_size;
  bitset = new boost::dynamic_bitset<>(init_size);
};

BloomFilter::~BloomFilter(){
  delete bitset;
};

void BloomFilter::add(string item){
  int * keys = this->keys(item);
  (*bitset).set(abs(keys[0]), true);
  (*bitset).set(abs(keys[1]), true);
  (*bitset).set(abs(keys[2]), true);
  delete [] keys;
};

bool BloomFilter::include(string item){
  int * keys = this->keys(item);
  bool result = (*bitset).test(keys[0]) && (*bitset).test(keys[1]) && (*bitset).test(keys[2]);
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
