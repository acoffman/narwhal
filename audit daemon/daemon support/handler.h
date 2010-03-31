#ifndef HANDLER_H
#define HANDLER_H

#include "../bloom/bloomfilter.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <vector>
#include <string>
#include <cmath>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define TABLE "narwhal_development"

#define FP_PERCENT 0.01
#define NUM_PROTOCOLS 141

struct bloom_ctl{
  char* bits;
  char* protocols;
  int size;
};

struct stat_ctl{
  unsigned long numPackets;
  unsigned long numDroppedPackets;
  unsigned long totalData;
};

#define BLOOM_IOCTL  _IOW('c', 10, struct bloom_ctl)
#define STAT_IOCTL  _IOR('c', 11, struct stat_ctl)

class NotificationHandler {
  public:
    NotificationHandler(int userid);
    ~NotificationHandler();

  private:
    int userid;
    BloomFilter * filter;
    vector<string> keyList;
    sql::Driver * driver;
    sql::Connection * con;
    sql::Statement * stmnt;
    sql::ResultSet * res;
    int calculateFilterSize();
    void createFilter();
    void mapBits();
    char * getProtoArray();
    void generateKeys();
};
#include "handler.cpp"
#endif


