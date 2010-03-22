NotificationHandler::NotificationHandler(int userid){
  this->userid = userid;
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  TABLE);
  performQuery();
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

void NotificationHandler::performQuery(){
  res = stmnt->executeQuery("SELECT ip FROM blockeds"); 
};

void NotificationHandler::generateKeys(){
  while (res->next()) {
    keyList.push_back(res->getString("name"));
  }
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
