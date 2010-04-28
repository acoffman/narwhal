StatsNotificationHandler::StatsNotificationHandler(){
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  DB);
  getKernelStats();
  //saveData();
};

StatsNotificationHandler::~StatsNotificationHandler(){
  delete con;
  delete stmnt;
};

void StatsNotificationHandler::getKernelStats(){
  int file_desc = open("/dev/ti0", O_RDWR);
  int * myint; 
  //ioctl(file_desc,STAT_IOCTL,&currentStats);
  ioctl(file_desc,STAT_IOCTL,myint);
  close(file_desc);
  cout << *myint << endl;
  delete myint;
};

void StatsNotificationHandler::saveData(){
  //string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
  //string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
  //string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
  //cout << packets << ":" << dropped << ":" << traffic << endl;
  //stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
