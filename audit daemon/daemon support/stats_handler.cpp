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
  //delete currentStats;
};

void StatsNotificationHandler::getKernelStats(){
  currentStats = &stat_struct; 
  int file_desc = open("/dev/ti0", O_RDWR);
  ioctl(file_desc,STAT_IOCTL,myint);
  close(file_desc);
};

void StatsNotificationHandler::saveData(){
  cout << myint << endl;
  //string packets = boost::lexical_cast<std::string>(currentStats->numPackets);
  //string dropped = boost::lexical_cast<std::string>(currentStats->numDroppedPackets);
  //string traffic = boost::lexical_cast<std::string>(currentStats->totalData);
  //cout << packets << ":" << dropped << ":" << traffic << ":" << endl;
  //stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
