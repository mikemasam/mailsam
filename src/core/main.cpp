#include <iostream>
#include "../options/options.h"
#include "../database/db_connect.h"

using namespace std;

int main(int ac, char** av){
  std::cout << "Starting up" << std::endl;
  Options op;
  if(!op.init(ac,av)){
    return 0;
  }
  string str = op.getStringValue("value");

  if(str.empty()){
    std::cout << "No Query = " << str << std::endl;
    return 0;
  }
  std::cout << "Query = " << str << std::endl;

  Connect *db = new Connect("tcp://127.0.0.1:3306","root","mtanzania","adverter");
  if(db->open()){
    db->test(str);
    db->close();
  }else{
    std::cout << "Failed to open connection: Query - " << str << std::endl;
  }
  return 0;
}
