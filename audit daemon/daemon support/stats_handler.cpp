StatsNotificationHandler::StatsNotificationHandler(){
  driver = get_driver_instance();
  con = driver->connect(HOST, USER, PASS);
  stmnt = con->createStatement();
  stmnt->execute("use "  DB);
	cout << "Called" << endl;
  getKernelStats();
	cout << "Call Win1" << endl;
  //saveData();
};

StatsNotificationHandler::~StatsNotificationHandler(){
  delete con;
  delete stmnt;
};

void StatsNotificationHandler::getKernelStats(){
  int file_desc = open("/dev/ti0", O_RDWR);
  long data[3];
  struct stat_ctl stats;
  stats.p = data;
  stats.s = sizeof data;
	cout << "Sending STAT_IOCTL command" << endl; 
  ioctl(file_desc,STAT_IOCTL,&stats);
  close(file_desc);
	long * temp = (long *)stats.p;
	cout << (temp) << endl;
	cout << "finished copy" << endl;
};

void StatsNotificationHandler::saveData(){
  //string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
  //string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
  //string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
  //cout << packets << ":" << dropped << ":" << traffic << endl;
  //stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
