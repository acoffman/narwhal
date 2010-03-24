NotificationHandler::NotificationHandler(int userid){
  this->userid = userid;
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  TABLE);
  generateKeys();
  createFilter();
  mapBits();
};

NotificationHandler::~NotificationHandler(){
  delete con;
  delete stmnt;
  delete res;
  delete filter;
};

void NotificationHandler::createFilter(){
  filter = new BloomFilter(calculateFilterSize());
  for(int i =0; i < keyList.size(); i++){
    (*filter).add(keyList.at(i));
  }
};

void NotificationHandler::generateKeys(){
  res = stmnt->executeQuery("SELECT ip FROM blockeds"); 
  while (res->next()) {
    keyList.push_back(res->getString("ip"));
  }
};

int NotificationHandler::calculateFilterSize(){
  int result = (int) (abs(ceil((keyList.size() * log(FP_PERCENT))/(log(2) * log(2)))));
  if(result <  100)
    return 100;
  return result;
};

char * NotificationHandler::getProtoArray(){
  char * protos =  new char[BITNSLOTS(NUM_PROTOCOLS)];
  for(int i =0; i < NUM_PROTOCOLS; i++)
    BITCLEAR(bitarry,i);

  res = stmnt->executeQuery("SELECT protocol FROM solo_protocols");
  while(res->next()){
    BITSET(protos, res->getInt("protocol"));    
  }
  return protos;
};

void NotificationHandler::mapBits(){
  int file_desc = open("/dev/ti0", O_RDWR);
  bloom_ctl bloom;
  bloom.bits = (*filter).getBitArray();
  bloom.size = BITNSLOTS((*filter).getSize());
  bloom.protocols = getProtoArray();
  ioctl(file_desc,BLOOM_IOCTL,&bloom);
  close(file_desc);
  delete [] bloom.protocols;
  delete [] bloom.bits;
};
