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

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define TABLE "tablename"

#define FP_PERCENT 0.95

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

};
#include "handler.cpp"
#endif


