#include <iostream>
#include <pthread.h>
#include <string.h>
#include <mailio/message.hpp>
#include <mailio/imap.hpp>
#include <mailio/smtp.hpp>
#include <mailio/mime.hpp>
#include "imap.h"

//using mailio::message;
//using mailio::codec;

Imap::~Imap(){
  this->mail_reader_running = false;
}

Imap::Imap(std::string account_mail,std::string account_password,std::string imap_host,int imap_port){
  this->account_mail = account_mail;
  this->account_password = account_password;
  this->imap_host = imap_host;
  this->imap_port = imap_port;
  if(this->debugging)
      std::cout << "imap_host = " << this->imap_host << " imap_port" << this->imap_port << std::endl;
}

void Imap::hold(){
    this->mail_reader_pause = true;
}

void Imap::resume(){
    this->mail_reader_pause = false;
}

bool Imap::accept(){
  // Thread id
  pthread_t threadId;
  // Create a thread that will function threadFunc()
  int err = pthread_create(&threadId, NULL, (THREADFUNCPTR) &Imap::pthread_created, this);
  // Check if thread is created sucessfuly
  if (err){
    if(this->debugging)
      std::cout << "Thread creation failed : " << strerror(err);
    return false;
  }else{
    if(this->debugging)
      std::cout << "Thread Created with ID : " << threadId << std::endl;
    return true;
  }
}

void *Imap::pthread_created(void *obj){
  Imap *myObj = reinterpret_cast<Imap *>(obj);
  myObj->_accept();
  return NULL;
}

void Imap::_accept(){
  mailio::imaps *conn = this->_connect();
  if(conn != NULL){
    if(this->debugging)
      std::cout << std::endl << "Connected;" << std::endl;
    mail_reader_running = true;
    this->_read(conn);
    std::cout << std::endl << "Connection closed;" << std::endl;

    delete conn;

  }else{
    std::cout << std::endl << "Connection failed;" << std::endl;
  }
}

mailio::imaps* Imap::_connect(){
  try{
    mailio::imaps *conn;

    if(this->debugging)
      std::cout << "imap_host = " << this->imap_host << " imap_port" << this->imap_port << std::endl;

    conn = new mailio::imaps(this->imap_host, this->imap_port);
    conn->authenticate(this->account_mail, this->account_password, mailio::imaps::auth_method_t::LOGIN);
    return conn;
  }catch(std::exception& e){
    if(this->debugging)
      std::cout << e.what() << std::endl;
    return NULL;
  }
}

void Imap::_read(mailio::imaps *conn){
  int index = 0;
  int no_stats_count = 0;
  if(debugging)
    std::cout << "Waiting for new message..." << std::endl;

  do{     
    try{
      if(mail_reader_pause)
        continue;

      if(debugging)
        std::cout << "values local=" << this->last_message_index << ", server=" << index << std::endl;

      mailio::imaps::mailbox_stat_t stat = conn->statistics("inbox");

      index = stat.messages_no;

      if(this->last_message_index < 1){
        this->last_message_index = stat.messages_no;
        std::cout << "new local index =" << this->last_message_index << std::endl;
      }

      if(index > this->last_message_index){
        this->last_message_index++;
        if(debugging)
          std::cout << "new message index = " << this->last_message_index << std::endl;
        this->_new_data(this->last_message_index);
      }else{
        if(debugging)
          std::cout << "No new message..." << std::endl;
      }
      no_stats_count = 0;
    }catch(std::exception& e){
      no_stats_count++;
      std::cout << e.what() << std::endl;
      if(no_stats_count > 5){
        this->mail_reader_running = false;
        break;
      }
    }
    sleep(5);
  } while(this->mail_reader_running);
}

bool Imap::_new_data(int new_index){
  try{
    mailio::imaps *conn = new mailio::imaps(this->imap_host, this->imap_port);
    conn->authenticate(this->account_mail, this->account_password, mailio::imaps::auth_method_t::LOGIN);
    mailio::message msg;
    msg.line_policy(mailio::codec::line_len_policy_t::MANDATORY);
    conn->fetch("inbox", new_index, msg);
    std::cout << msg.subject() << std::endl;
    //if(msg.content_type() == mailio::mime::media_type_t::MULTIPART){

    //}else if(msg.content_type() == mailio::mime::media_type_t::TEXT){

    //}

    std::cout << "MULTIPART = " << (msg.content_type().type == mailio::mime::media_type_t::MULTIPART) << std::endl;

    std::cout << "TEXT = " << (msg.content_type().type == mailio::mime::media_type_t::TEXT) << std::endl;

    if(msg.content_type().type == mailio::mime::media_type_t::MULTIPART){
      for (mailio::mime _msg: msg.parts()) {  
        std::string data = _msg.content();
        std::cout << data << std::endl;
      }
    }else if (msg.content_type().type == mailio::mime::media_type_t::TEXT){
        std::string data = msg.content();
        std::cout << data << std::endl;
    }
    delete conn;
    return true;
  }catch(std::exception& e){
    std::cout << e.what() << std::endl;
  }
  return false;
}

void Imap::close(){
  this->mail_reader_running = false;
}

bool Imap::read(int index){
  return this->_new_data(index);
}
