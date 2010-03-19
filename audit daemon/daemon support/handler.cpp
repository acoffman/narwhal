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
};

int NotificationHandler::calculateFilterSize(){
  return (int) (10 * abs(ceil((keyList.size() * log(FP_PERCENT))/(log(2) * log(2)))));
};

void NotificationHandler::mapBits(){
  //map bits into kernel space
};
