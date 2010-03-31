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
};

void StatsNotificationHandler::getKernelStats(){
  int file_desc = open("/dev/ti0", O_RDWR);
  ioctl(file_desc,STAT_IOCTL,&currentStats);
  close(file_desc);
};

void StatsNotificationHandler::saveData(){
  string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
  string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
  string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
  stmnt->execute("INSERT INTO stats (numPackets, numDroppedPackets, totalData) VALUES (" + packets + ", " + dropped + ", " + traffic + " )"); 
};
