NotificationHandler::NotificationHandler(int userid){
  this->userid = userid;
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  DB);
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

  res = stmnt->executeQuery("SELECT * FROM rates");
  while(res->next()){
    string str_avg = res->getString("avg_rate");
    sscanf(str_avg.c_str(), "%f", &avg);
    string str_peak = res->getString("peak_rate");
    sscanf(str_peak.c_str(), "%f", &peak);
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
    BITCLEAR(protos,i);

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
  bloom.avg_rate = avg;
  bloom.peak_rate = peak;
  ioctl(file_desc,BLOOM_IOCTL,&bloom);
  close(file_desc);
  delete [] bloom.protocols;
  delete [] bloom.bits;
};
