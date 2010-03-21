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
  test();
};

NotificationHandler::~NotificationHandler(){
  //delete con;
  //delete stmnt;
  //delete res;
  delete filter;
};

void NotificationHandler::createFilter(){
  filter = new BloomFilter(ARRAY_SIZE);
  for(int i =0; i < keyList.size(); i++){
    (*filter).add(keyList.at(i));
  }
};

void NotificationHandler::performQuery(){
  //do db query here
};

void NotificationHandler::generateKeys(){
  //populate vector with keys from the query
   keyList.push_back("hello");
   keyList.push_back("hi");
   keyList.push_back("welcome");
   keyList.push_back("y helo thar");
   keyList.push_back("i hope this works");
};

int NotificationHandler::calculateFilterSize(){
  int result = (int) (abs(ceil((keyList.size() * log(FP_PERCENT))/(log(2) * log(2)))));
  if(result <  100)
    return 100;
  return result;
};

void NotificationHandler::mapBits(){
  int shmid;
  char * shm;
  if ((shmid = shmget(KEY, sizeof(char) * BITNSLOTS((*filter).getSize()), IPC_CREAT | PERMS)) < 0) {
    perror("shmget");
    exit(1);
  }  

  if ((shm = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("shmat");
    exit(1);
  }
  char * data = (*filter).getBitArray();
  char * detach = shm;
  for(int i = 0; i < BITNSLOTS((*filter).getSize()); i++)
    *shm++ = *data++;

  shmdt(detach);
  data = NULL;
  shm = NULL;
};

void NotificationHandler::test(){
  int shmid;
  char *shm, *filtr;

  filtr = (*filter).getBitArray();
  if ((shmid = shmget(KEY, sizeof(char) * BITNSLOTS((*filter).getSize()), PERMS)) < 0) {
    perror("shmget");
    exit(1);
  }

  if ((shm = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("shmat");
    exit(1);
  }

  char * detach = shm;

  for(int i = 0; i < BITNSLOTS((*filter).getSize()); i++){ 
    putchar(*filtr++);
    putchar(*shm++);
    cout << endl;
  }

  shmdt(detach);
  //shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
  
}
