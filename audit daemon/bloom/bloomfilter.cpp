int BloomFilter::djbHash(string item){
	 int hash = 5381;
   for(int i = 0; i < item.length(); i++)
      hash = ((hash << 5) + hash) + item[i];
   return hash;
};

BloomFilter::BloomFilter(int init_size){
  size = BITNSLOTS(init_size) * CHAR_BIT;
  bitarray = new char[BITNSLOTS(init_size)];

};

BloomFilter::~BloomFilter(){
  delete []  bitarray;
};

void BloomFilter::add(string item){
  int * keys = this->keys(item);
	BITSET(bitarray, ABS(keys[0]));
	BITSET(bitarray, ABS(keys[1]));
	BITSET(bitarray, ABS(keys[2]));
  cout << keys[0] << endl << keys[1] << endl << keys[2] << endl;
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
  keys[0] = ABS(djbHash(item) % size);
  keys[1] = ABS(djbHash(item1) % size);
  char * ti_con = ti_concat(item.c_str(), item1.c_str());
  string temp(ti_con);
  cout << temp << endl;
  keys[2] = ABS(djbHash(temp) % size);
  delete [] ti_con;
  return keys;
};

char * BloomFilter::getBitArray(){
  return bitarray;
};

int BloomFilter::getSize(){
  return size;
};

char * BloomFilter::ti_concat(const char * c1, const char * c2){
  int len = strlen(c1) + strlen(c2) + 1;
  char * c = (char *)malloc(len);
  if(c == NULL)
    return NULL;
  strcpy(c, c1);
  return strcat(c, c2);
};
