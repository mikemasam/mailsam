#include <iostream>
#include "../options/options.h"
#include "../mail/imap.h"
#include <iomanip>

using namespace std;

string smtp_host = "smtp.gmail.com";
int smtp_port = 587;
Imap *imap;
void terminal();

int main(int ac, char** av){
  terminal();
  return 0;
}


void start_reader(){
  if(imap == NULL){
    string a_m = "alltoall07@gmail.com";
    string a_p = "meshack07";
    string imap_host = "imap.gmail.com";
    imap = new Imap(a_m,a_p,imap_host);
  }
  imap->accept();
}

void stop_reader(){
  delete imap;
}


void new_emails(){

}



void terminal() {
  while(true){
    cout << "x:" << flush;
    string s;
    getline(std::cin, s);
    if(s == "boot")
      start_reader();
    if(s == "stop")
      stop_reader();
    if(s == "read")
      new_emails();
    if(s == "q"){
      stop_reader();
      return;
    }
  }
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
