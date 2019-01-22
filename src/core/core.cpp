#include <iostream>
#include "core.h" 
#include "../net/socket.h"
#include <future>
#include "utils.h"

Core::Core(){
  imap = NULL;
}
bool Core::init(int terminal_port){
  return initTerminal(terminal_port);
}


bool Core::initBackground(){
  return false;
}

bool Core::initTerminal(int terminal_port){
  Socket *soc = new Socket();
  if(!soc->init()){
    std::cout << "init failed" << std::endl;
    return 0;
  }
  if(!soc->server(terminal_port)){
    std::cout << "failed to bind " << terminal_port << std::endl;
    return 0;
  }
  while(Socket *new_sock = soc->acceptSocket()){
    std::cout << "new connection" << std::endl;
    Core *c = this;
    std::async([c,new_sock]{ return c->terminalUser(new_sock);});
  }
  delete soc;
  return false;
}

void Core::terminalUser(Socket *sock){
  sock->send_data("Welcome to Mailsam Terminal\n");
  std::string data;
  while(sock->recv_data(data)){
    std::string _rtn = terminal(data);
    sock->send_data(_rtn + "\r\n");
    data = "";
  }
}

std::string Core::terminal(std::string data){
  std::vector<std::string> x = Utils::split(data, ' ');
  if(x.size() < 1 )
    return "";

  std::string s = x.at(0);
  if(s == "connect"){
    if(x.size() == 3){
      return initMail(x.at(1),x.at(2));
    }else{
      return "Invalid Credentials";
    }
  }else if(s == "stop"){
    return stopMail();
  }else if(s == "status"){
    return imap != NULL ? imap->getLastError() : "Not Started";
  }else{
    return "Invalid Cammand:" + data;
  }

  return "";
}

std::string Core::initMail(std::string email,std::string password){
  if(imap == NULL){
    std::string imap_host = "imap.gmail.com";
    this->imap = new Imap(email,password,imap_host);
    this->imap->accept();
    if(this->imap->getLastError() != "")
      return this->imap->getLastError();
    return "Service Started ";
  }else{
    return "Service already started";
  }
}

std::string Core::stopMail(){
  if(this->imap != NULL){
    delete this->imap;
    this->imap = NULL;
    return "Service stoped";
  }
  return "Service not running";
}
