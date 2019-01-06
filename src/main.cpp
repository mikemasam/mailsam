#include <iostream>
#include "options/options.h"

using namespace std;

int main(int ac, char** av){
  std::cout << "Starting up" << std::endl;
  Options op;
  if(!op.init(ac,av)){
    return 0;
  }
  string user = op.getStringValue("user");
  cout << "User is = " << user << endl;
  return 0;
}
