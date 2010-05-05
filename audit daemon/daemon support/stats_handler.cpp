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
	long data[] = {0,1,2};
	struct stat_ctl stats;
	stats.p = data;
	stats.s = sizeof data;
	printf("%p\n", &stats);
	cout << "Sending STAT_IOCTL command" << endl; 

	if(ioctl(file_desc,STAT_IOCTL,stats) == -1){
		cout << strerror( errno ) << endl;
		close(file_desc);
		return;	
	}
	close(file_desc);
	long * temp = (long *)stats.p;
	cout << temp[0] << temp[1] << temp[2] << endl;
	cout << "finished copy" << endl;
};

void StatsNotificationHandler::saveData(){
	//string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
	//string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
	//string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
	//cout << packets << ":" << dropped << ":" << traffic << endl;
	//stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
