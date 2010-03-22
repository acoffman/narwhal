NotificationHandler::NotificationHandler(int userid){
  this->userid = userid;
  //driver = get_driver_instance();
  //con = driver->connect(HOST, USER, PASS);
  //stmnt = con->createStatement();
  //stmnt->execute("use "  TABLE);
  performQuery();
  generateKeys();
  createFilter();
  mapBits();
};

NotificationHandler::~NotificationHandler(){
  //delete con;
  //delete stmnt;
  //delete res;
  delete filter;
};

void NotificationHandler::createFilter(){
  filter = new BloomFilter(calculateFilterSize());
  for(int i =0; i < keyList.size(); i++){
    (*filter).add(keyList.at(i));
  }
};

void NotificationHandler::performQuery(){
  //do db query here
};

void NotificationHandler::generateKeys(){
  //populate vector with keys from the query
  keyList.push_back("10.1.1.1");
  keyList.push_back("10.1.1.254");
};

int NotificationHandler::calculateFilterSize(){
  int result = (int) (abs(ceil((keyList.size() * log(FP_PERCENT))/(log(2) * log(2)))));
  if(result <  100)
    return 100;
  return result;
};

void NotificationHandler::mapBits(){
  int file_desc = open("/dev/ti0", O_RDWR);
  bloom_ctl bloom;
  bloom.bits = (*filter).getBitArray();
  bloom.size = BITNSLOTS((*filter).getSize());
  ioctl(file_desc,BLOOM_IOCTL,&bloom);
  close(file_desc);
};
