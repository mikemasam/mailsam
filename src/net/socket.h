#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#pragma once
class Socket
{
 public:
  Socket();
  virtual ~Socket();

  // Server initialization
  bool init(int max_connection_count = 10);
  bool server(int port);
  Socket* acceptSocket ();

  // Client initialization
  bool client_connect(std::string host,int port);

  // Data Transimission
  bool send_data(std::string);
  bool recv_data(std::string&);

  void set_non_blocking ( const bool );

  bool is_valid() const { return m_sock != -1; }

 private:
  int m_sock;
  sockaddr_in m_addr;
  int max_cons = 5;
  //int max_recv = 1024;
  int max_recv = 30;
  bool debugging = false;
};

