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

	struct stat_ctl * stats_ptr;
	struct stat_ctl stats;
	stats.numPackets = 50;
	stats.numDroppedPackets = 50;
	stats.totalData = 50;
	stats_ptr = &stats;

	cout << "Sending STAT_IOCTL command" << endl; 
	if(ioctl(file_desc,STAT_IOCTL,stats_ptr) == -1){
		cout << strerror( errno ) << endl;
		close(file_desc);
		return;	
	}
	close(file_desc);
	cout << stats.numPackets << endl;
	cout << "finished copy" << endl;
};

void StatsNotificationHandler::saveData(){
	//string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
	//string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
	//string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
	//cout << packets << ":" << dropped << ":" << traffic << endl;
	//stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
