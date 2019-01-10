#include "db_connect.h"
#include "../includes/mysql/mysql_connection.h"
#include "../includes/mysql/cppconn/driver.h"
#include "../includes/mysql/cppconn/exception.h"
#include "../includes/mysql/cppconn/resultset.h"
#include "../includes/mysql/cppconn/statement.h"
#include "../includes/mysql/cppconn/prepared_statement.h"

using namespace std;
Connect::Connect(string net,string user,string password,string db){

  this->_db = db;
  this->_net = net;
  this->_user = user;
  this->_password = password;

  try{
  /* Create a connection */
    driver = get_driver_instance();
  }catch(sql::SQLException &e){
  }
}

bool Connect::open(){
  try{
    this->con = this->driver->connect(this->_net, this->_user, this->_password);
    /* Connect to the MySQL test database */
    this->con->setSchema(this->_db);
  } catch(sql::SQLException &e){
    return false;
  }
  return true;
} 

bool Connect::state(){
  return this->con->isValid();
}

void Connect::close(){
  delete this->con;
}

sql::ResultSet* Connect::execute(string sql){

  sql::PreparedStatement *stmt;
  sql::ResultSet *res;

  try{
    stmt = this->con->prepareStatement(sql);
    res = stmt->executeQuery();
  } catch(sql::SQLException &e){
    cout << "Query failed with : " << e.what() << endl << "Query:" << sql << endl;
    return NULL;
  }
  return res;
}

void Connect::test(string str){
  if(!this->state())
    return;

  sql::ResultSet *res = this->execute(str);
  if(res == NULL){
    return;
  }

  sql::ResultSetMetaData *res_meta = res->getMetaData();
  int columns = res_meta->getColumnCount();

  //Loop for each row
  while (res->next()) {
    /* Access column data by index, 1-indexed*/
    cout << "--------------------------------------" << endl;
    for (int i = 1; i <= columns; i++) {
      cout << res->getString(i) << "|" ;
    }
    cout << endl;
  }
  delete res;
}


