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
#include <sys/ipc.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <errno.h>

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define TABLE "tablename"

#define FP_PERCENT 0.01

#define KEY ftok("/",5432)
#define KEY_SIZE ftok("/", 5431)

#define PERMS 0666

#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

#define TIBLOOMFILTER _IOW(0,253,char*)
#define ZIVA_IOCTL  _IOW('c', 10, int)

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
    void performQuery();
    int calculateFilterSize();
    void createFilter();
    void mapBits();
    void generateKeys();
    void test();

};
#include "handler.cpp"
#endif


