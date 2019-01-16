#include <iostream>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#pragma once

class Smtp{
  public:
    Smtp(std::string account_mail,std::string account_password,std::string smtp_host,int smpt_port);
    bool connect();
    bool send(std::string recepient,std::string subject,std::string content);
    ~Smtp();
  private:
    std::string account_mail;
    std::string account_password;
    std::string smtp_host;
    int smtp_port = 0;
    mailio::smtps *conn;
    bool debugging = false;
};
