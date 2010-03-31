StatsNotificationHandler::StatsNotificationHandler(){
  cout << "CONSTRUCT" << endl;
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  DB);
  cout << "BEFORE STATS" << endl;
  getKernelStats();
  cout << "AFTER STATS" << endl;
  saveData();
  cout << "AFTER SAVE" << endl;
};

StatsNotificationHandler::~StatsNotificationHandler(){
  delete con;
  delete driver;
  delete stmnt;
};

void StatsNotificationHandler::getKernelStats(){
  int file_desc = open("/dev/ti0", O_RDWR);
  cout << "DESC OPEN" << endl;
  ioctl(file_desc,STAT_IOCTL,&currentStats);
  cout << "IOCTL DONE" << endl;
  close(file_desc);
};

void StatsNotificationHandler::saveData(){
  string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
  string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
  string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
  cout << packets << ":" << dropped << ":" << traffic << ":" << endl;
  stmnt->execute("INSERT INTO stats (numPackets, numDroppedPackets, totalData) VALUES (" + packets + ", " + dropped + ", " + traffic + " )"); 
  cout << "AFTER INSERT" << endl;
};
