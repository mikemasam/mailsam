#include <mailio/imap.hpp>
#include <iostream>

#pragma once

class Imap{
  public:
    Imap(std::string account_mail,std::string account_password,std::string imap_host,int imap_port = 993);
    ~Imap();
    bool accept();
    void close();
    void hold();
    void resume();
    bool read(int index);
    bool debugging = false;
    void _accept();
    static void *pthread_created(void *);
    std::string getLastError();
  private:
    mailio::imaps* _connect();
    void _read(mailio::imaps*);
    bool _new_data(int);
    std::string content(mailio::mime *);
    int last_message_index = 0;
    //control flags
    bool mail_reader_running = false;
    bool mail_reader_pause = false;
    //credentials and other required data
    int imap_port = 993;
    std::string imap_host = "";
    std::string account_mail = "";
    std::string account_password = "";
    std::string last_error = "";
};
typedef void * (*THREADFUNCPTR)(void *);
