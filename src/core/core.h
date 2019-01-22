#include <iostream>
#include "../net/socket.h"
#include "../mail/imap.h"
#pragma once
class Core {
  public:
    Core();
    //start the background process
    //start socket terminal
    bool init(int);
    std::string terminal(std::string);
  private:
    bool initTerminal(int);
    void terminalUser(Socket*);
    bool initBackground();
    std::string initMail(std::string,std::string);
    std::string stopMail();
    Imap *imap;
};
