#include <iostream>
//#include "options/options.h"
#include <iomanip>
#include "core/core.h"

std::string smtp_host = "smtp.gmail.com";
int smtp_port = 587;

int main(int ac, char** av){
  Core core;
  core.init(9000);
  return 0;
}


/*
   Socket *soc = new Socket();
   if(!soc->init()){
   std::cout << "init failed" << endl;
   return 0;
   }
   if(!soc->server(9000)){
   std::cout << "failed to bind 9000" << endl;
   return 0;
   }
   Socket new_sock;
   if(soc->acceptSocket(new_sock)){
   std::cout << "new connection" << endl;
   std::string data = "";
   while(new_sock.recv_data(data)){
   std::cout << "new data = " << escape_cpp(data) << endl;
   data = "";
   }
   }
   delete soc;
   */

//  Options op;
//  if(!op.init(ac,av)){
//    return 0;
//  }

//  string str = op.getStringValue("value");
//
//  if(str.empty()){
//    std::cout << "No Value = " << str << std::endl;
//    str = "1";
//  }else{
//    std::cout << "Value = " << str << std::endl;
//  }
