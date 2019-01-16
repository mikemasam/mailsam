// Implementation of the Socket class.
#include <iostream>
#include "socket.h"
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>



Socket::Socket() {
  this->m_sock = -1;
  memset(&this->m_addr,0,sizeof(this->m_addr));
}

Socket::~Socket(){
  if (is_valid()){
    //::close ( m_sock );
  }
}

bool Socket::init(int max_connection_count){
  this->max_cons = max_connection_count;
  //initiliaze socket file descripter
  m_sock = socket(AF_INET,SOCK_STREAM,0);
  if(!is_valid())
    return false;

  // TIME_WAIT - argh
  int on = 1;
  if (setsockopt(m_sock,SOL_SOCKET,SO_REUSEADDR,(const char*)&on, sizeof(on)) == -1 )
    return false;
  return true;
}

bool Socket::server(int port){
  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons (port);

  if (bind(m_sock,(struct sockaddr *) &m_addr,sizeof(m_addr)) != 0){
    return false;
  }

  if (listen(m_sock, this->max_cons) == -1){
    return false;
  }
  //this->set_non_blocking(true);
  return true;
}



bool Socket::acceptSocket (Socket& new_socket){
  int addr_length = sizeof ( m_addr );
  new_socket.m_sock = accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

  if ( new_socket.m_sock <= 0 )
    return false;
  else
    return true;
}


bool Socket::send_data(std::string s) {
  int status = send(m_sock, s.c_str(), s.size(), MSG_NOSIGNAL);
  if (status == -1){
    return false;
  }
  else{
    return true;
  }
}


bool Socket::recv_data(std::string& s) {
  if(!is_valid())
    return false;
  char buf[this->max_recv];
  memset(buf, 0, this->max_recv);
  int status = this->max_recv;

  while(status >= this->max_recv){
    status = recv(m_sock, buf, this->max_recv, 0);
    s.append(buf, status);
    if(this->debugging)
    std::cout << "buffer = " << buf << " , size " << status << std::endl;
    memset(buf, 0, this->max_recv);
  }

  if(this->debugging)
  std::cout << "end receiving" << std::endl;
  return status > 0;
}


bool Socket::client_connect(std::string host,int port){
  if (!is_valid())
    return false;

  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons ( port );
  int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
  if (status != 1)
    return false;
  status = connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));
  if(status == 0)
    return true;
  else
    return false;
}

void Socket::set_non_blocking ( const bool b ){
  int opts;
  opts = fcntl(m_sock,F_GETFL );
  if (opts < 0){
    return;
  }
  if(b)
    opts = (opts | O_NONBLOCK);
  else
    opts = (opts & ~O_NONBLOCK);
  fcntl(m_sock,F_SETFL,opts);
} 
