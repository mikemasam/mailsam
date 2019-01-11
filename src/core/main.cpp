#include <iostream>
#include "../options/options.h"
#include <mailio/message.hpp>
#include <mailio/imap.hpp>

using mailio::imaps;
using mailio::imap;
using mailio::imap_error;
using mailio::dialog_error;
using mailio::message;
using mailio::codec;

using namespace std;
imaps *conn;
bool connect();
void read_new_message(int new_index);
void message_reader();


int main(int ac, char** av){

  if(connect()){
    std::cout << "Connected" << std::endl;
    message_reader();
  }else{
    std::cout << "Connection failed" << std::endl;
    return 1;
  }
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


  return 0;
}

bool connect(){
  try{
    conn = new imaps("imap.gmail.com", 993);
    conn->authenticate("alltoall07@gmail.com", "meshack07", imaps::auth_method_t::LOGIN);
  }catch(exception& e){
    cout << e.what() << endl;
    return false;
  }
  return true;
}

int newest_index = 0;
void message_reader(){
  bool first_call = true;
  int index = 0;
  int no_stats_count = 0;
  cout << "Waiting for new message..." << endl;

  do{     
    try{
      cout << "values local=" << newest_index << ", server=" << index << endl;
      imaps::mailbox_stat_t stat = conn->statistics("inbox");
      index = stat.messages_no;
      if(first_call){
        newest_index = stat.messages_no;
        first_call = false;
      }else if(index > newest_index){
        newest_index++;
        cout << "new message index = " << newest_index  << endl;
        read_new_message(newest_index);
      }else{
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
  } while(true);
}

void read_new_message(int new_index){
  try{
    imaps *conn = new imaps("imap.gmail.com", 993);
    conn->authenticate("alltoall07@gmail.com", "meshack07", imaps::auth_method_t::LOGIN);
    message msg;
    msg.line_policy(codec::line_len_policy_t::MANDATORY);
    conn->fetch("inbox", new_index, msg);
    cout << msg.subject() << endl;
    cout << msg.content() << endl;
  }catch(exception& e){
    cout << e.what() << endl;
  }
}
void send_message(){

}
