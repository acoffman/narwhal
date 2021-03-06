#ifndef STATS_HANDLER_H
#define STATS_HANDLER_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <boost/lexical_cast.hpp>

#include <string>

#include <iostream>

#include <errno.h>

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "narwhal_development"

struct stat_ctl{
  unsigned long numPackets;
  unsigned long numDroppedPackets;
  unsigned long totalData;
};

#define STAT_IOCTL  _IOR('c', 11, struct stat_ctl)

class StatsNotificationHandler {
  public:
    StatsNotificationHandler();
		~StatsNotificationHandler();

  private:
    sql::Driver * driver;
    sql::Connection * con;
    sql::Statement * stmnt;
    void getKernelStats();
    void saveData();
    stat_ctl * stats_ptr;
};

#include "stats_handler.cpp"
#endif
