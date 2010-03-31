StatsNotificationHandler::StatsNotificationHandler(){
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  DB);
  getKernelStats();
  saveData();
};

StatsNotificationHandler::~StatsNotificationHandler(){
  delete con;
  delete stmnt;
  free(currentStats);
};

void StatsNotificationHandler::getKernelStats(){
  int file_desc = open("/dev/ti0", O_RDWR);
  currentStats = (struct stat_ctl *)malloc(sizeof(struct stat_ctl));
  ioctl(file_desc,STAT_IOCTL,&currentStats);
  close(file_desc);
};

void StatsNotificationHandler::saveData(){
  string packets = boost::lexical_cast<std::string>(currentStats->numPackets);
  string dropped = boost::lexical_cast<std::string>(currentStats->numDroppedPackets);
  string traffic = boost::lexical_cast<std::string>(currentStats->totalData);
  cout << packets << ":" << dropped << ":" << traffic << endl;
  //stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
