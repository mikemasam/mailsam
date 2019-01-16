#include <iostream>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include "smtp.h"

Smtp::~Smtp(){
  delete this->conn;
}

Smtp::Smtp(std::string account_mail,std::string account_password,std::string smtp_host,int smtp_port){
  this->account_mail = account_mail;
  this->account_password = account_password;
  this->smtp_host = smtp_host;
  this->smtp_port = smtp_port;
}

bool Smtp::connect(){
  try{
    conn = new mailio::smtps(this->smtp_host, this->smtp_port);
    this->conn->authenticate(this->account_mail, this->account_password, mailio::smtps::auth_method_t::START_TLS);
    return true;
  }catch(std::exception& e){
    return false;
  }
}

bool Smtp::send(std::string recepient,std::string subject,std::string content){
  try {
    mailio::message msg;
    msg.from(mailio::mail_address(this->account_mail, this->account_mail));// set the correct sender name and address
    msg.add_recipient(mailio::mail_address(recepient, recepient));// set the correct recipent name and address
    msg.subject(subject);
    msg.content(content);
    this->conn->submit(msg);
  }catch (std::exception& e){
    if(this->debugging)
      std::cout << e.what() << std::endl;
  }
}
