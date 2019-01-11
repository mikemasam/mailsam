#include <iostream>
#include <pthread.h>
#include "../options/options.h"
#include <mailio/message.hpp>
#include <mailio/imap.hpp>
#include <mailio/smtp.hpp>

using mailio::imaps;
using mailio::imap;

using mailio::smtps;
using mailio::mail_address;

using mailio::message;
using mailio::codec;

using namespace std;
string account_mail = "alltoall07@gmail.com";
string account_password = "meshack07";
string imap_host = "imap.gmail.com";
string smtp_host = "smtp.gmail.com";
int imap_port = 993;
int smtp_port = 587;
bool mail_reader_running = false;
bool mail_reader_pause = false;
bool debugging = false;

int newest_index = 0;
bool first_call = true;



imaps* connect_imap();
void read_new_message(int new_index);
void message_reader(imaps *conn);
void start_reader();
void stop_reader();
void send_message();
void *_start_reader(void *);
void terminal();



int main(int ac, char** av){

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
  terminal();
  return 0;
}

void terminal()
{
  while(true){
    cout << "x:" << flush;
    string s;
    getline(std::cin, s);
    if(s == "read")
      start_reader();
    if(s == "stop")
      stop_reader();
    if(s == "new")
      send_message();
    if(s == "q"){
      stop_reader();
      return;
    }
  }
  //cout << "the string was: " << s << std::endl;
}
//thread safe
void stop_reader(){
  mail_reader_running = false;
}

void *_start_reader(void *){
  imaps *conn = connect_imap();
  if(conn != NULL){
    std::cout << endl << "Connected;" << std::endl;
    mail_reader_running = true;
    message_reader(conn);
    std::cout << endl << "Connection closed;" << std::endl;
    delete conn;
  }else{
    std::cout << endl << "Connection failed;" << std::endl;
  }
  return NULL;
}
void start_reader(){
  // Thread id
  pthread_t threadId;
  // Create a thread that will function threadFunc()
  int err = pthread_create(&threadId, NULL, &_start_reader, NULL);
  // Check if thread is created sucessfuly
  if(debugging){
    if (err){
      cout << "Thread creation failed : " << strerror(err);
    }else{
      cout << "Thread Created with ID : " << threadId << endl;
    }
  }
}

imaps* connect_imap(){
  try{
    imaps *conn;
    conn = new imaps(imap_host, imap_port);
    conn->authenticate(account_mail, account_password, imaps::auth_method_t::LOGIN);
    return conn;
  }catch(exception& e){
    cout << e.what() << endl;
    return NULL;
  }
}

void message_reader(imaps *conn){
  int index = 0;
  int no_stats_count = 0;
  if(debugging)
    cout << "Waiting for new message..." << endl;

  do{     
    try{
      if(mail_reader_pause)
        continue;

      if(debugging)
        cout << "values local=" << newest_index << ", server=" << index << endl;
      imaps::mailbox_stat_t stat = conn->statistics("inbox");
      index = stat.messages_no;
      if(first_call){
        newest_index = stat.messages_no;
        first_call = false;
      }else if(index > newest_index){
        newest_index++;
        if(debugging)
          cout << "new message index = " << newest_index  << endl;
        read_new_message(newest_index);
      }else{
        if(debugging)
          cout << "No new message..." << endl;
      }
      no_stats_count = 0;
    }catch(exception& e){
      no_stats_count++;
      cout << e.what() << endl;
      if(no_stats_count > 5)
        break;
    }
    sleep(2);
  } while(mail_reader_running);
}

void read_new_message(int new_index){
  try{
    imaps *conn = new imaps(imap_host, imap_port);
    conn->authenticate(account_mail, account_password, imaps::auth_method_t::LOGIN);
    message msg;
    msg.line_policy(codec::line_len_policy_t::MANDATORY);
    conn->fetch("inbox", new_index, msg);
    cout << msg.subject() << endl;
    cout << msg.content() << endl;
    delete conn;
  }catch(exception& e){
    cout << e.what() << endl;
  }
}

void send_message(){
  try {

    string recepient;
    cout << "Recepient:" << flush;
    getline(std::cin, recepient);

    string title;
    cout << "Title:" << flush;
    getline(std::cin, title);

    string content;
    cout << "Content:" << flush;
    getline(std::cin, content);

    message msg;
    msg.from(mail_address("mailio library", account_mail));// set the correct sender name and address
    msg.add_recipient(mail_address("mailio library", recepient));// set the correct recipent name and address
    msg.subject(title);
    msg.content(content);

    smtps *conn = new smtps(smtp_host, smtp_port);
    conn->authenticate(account_mail, account_password, smtps::auth_method_t::START_TLS);
    conn->submit(msg);
    delete conn;
  }catch (exception& exc){
    cout << exc.what() << endl;
  }
}

