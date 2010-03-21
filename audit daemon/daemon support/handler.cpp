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
  int result = (int) (10 * abs(ceil((keyList.size() * log(FP_PERCENT))/(log(2) * log(2)))));
  if(result <  100)
    return 100;
  return result;
};

void NotificationHandler::mapBits(){
  //map bits into kernel space
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
  char * curr = shm;
  for(int i = 0; i < BITNSLOTS((*filter).getSize()); i++)
    *shm++ = *data++;
  curr = NULL;
  data = NULL;
  shm = NULL;

  if((shmid = shmget(SIZE_KEY, sizeof(int), IPC_CREAT | PERMS )) < 0){
    perror("shmget");
    exit(1);
  }

  int * shm_size;
  if((shm_size = (int *) shmat(shmid, NULL, 0)) == (int *) -1){
    perror("shmget");
    exit(1);
  }

  *shm_size = (*filter).getSize();
};

void NotificationHandler::test(){
  int shmid;
  key_t key;
  char *shm, *s, *filtr;
  int * shm_size;

  filtr = (*filter).getBitArray();
  if ((shmid = shmget(KEY, sizeof(char) * BITNSLOTS((*filter).getSize()), PERMS)) < 0) {
    perror("shmget");
    exit(1);
  }

  if ((shm = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("shmat");
    exit(1);
  }


  for(int i = 0; i < BITNSLOTS((*filter).getSize()); i++){ 
    putchar(*filtr++);
    putchar(*shm++);
    cout << endl;
  }

  
  if((shmid = shmget(SIZE_KEY, sizeof(int), IPC_CREAT | PERMS )) < 0){
    perror("shmget");
    exit(1);
  }

  if((shm_size = (int *) shmat(shmid, NULL, 0)) == (int *) -1){
    perror("shmget");
    exit(1);
  }

  cout << endl << endl << (*filter).getSize() << " " << *shm_size;

}
