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

	stat_ctl * stats_ptr = new stat_ctl;
	stats_ptr->numPackets = 50;
	stats_ptr->numDroppedPackets = 50;
	stats_ptr->totalData = 50;

	cout << "Sending STAT_IOCTL command" << endl; 
	cout << &stats_ptr << endl;
	if(ioctl(file_desc,STAT_IOCTL ,stats_ptr) == -1){
		cout << strerror( errno ) << endl;
		close(file_desc);
		return;	
	}
	close(file_desc);
	cout << stats_ptr->numPackets << endl;
	cout << "finished copy" << endl;
};

void StatsNotificationHandler::saveData(){
	//string packets = boost::lexical_cast<std::string>(currentStats.numPackets);
	//string dropped = boost::lexical_cast<std::string>(currentStats.numDroppedPackets);
	//string traffic = boost::lexical_cast<std::string>(currentStats.totalData);
	//cout << packets << ":" << dropped << ":" << traffic << endl;
	//stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
