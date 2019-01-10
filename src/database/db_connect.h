#pragma once
#include <string>
#include "../includes/mysql/mysql_connection.h"
#include "../includes/mysql/cppconn/driver.h"
#include "../includes/mysql/cppconn/resultset.h"
using namespace std;
class Connect {
  public:
    Connect(string net,string user,string password,string db);
    bool open();
    void close();
    bool state();
    void test(string str);
    sql::ResultSet* execute(string sql);
  private:
    sql::Driver *driver;
    sql::Connection *con;
    string _net,_user,_password,_db;
};
