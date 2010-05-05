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

	stats_ptr = new stat_ctl;
	stats_ptr->numPackets = 0;
	stats_ptr->numDroppedPackets = 0;
	stats_ptr->totalData = 0;

	if(ioctl(file_desc,STAT_IOCTL ,stats_ptr) == -1){
		cout << strerror( errno ) << endl;
		close(file_desc);
		delete stats_ptr;
		return;	
	}
	close(file_desc);
	cout << stats_ptr->numPackets << endl;
	cout << stats_ptr->numDroppedPackets << endl;
	cout << stats_ptr->totalData << endl;
	cout << "finished copy" << endl;
	delete stats_ptr;
};

void StatsNotificationHandler::saveData(){
	string packets = boost::lexical_cast<std::string>(stats_ptr->numPackets);
	string dropped = boost::lexical_cast<std::string>(stats_ptr->numDroppedPackets);
	string traffic = boost::lexical_cast<std::string>(stats_ptr->totalData);
	stmnt->execute("INSERT INTO stats (created_at, numPackets, numDroppedPackets, totalData) VALUES (NOW()," + packets + ", " + dropped + ", " + traffic + " )"); 
};
