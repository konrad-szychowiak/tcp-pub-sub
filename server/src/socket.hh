//
// Created by konrad on 27.12.2021.
//

#ifndef SERVER_SOCKET_HH
#define SERVER_SOCKET_HH

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <pthread.h>
#include <iostream>

class Socket
{
private:
  int server_socket_descriptor;
  struct sockaddr_in server_address;

public:
  int
  _init(int port);

  int
  _bind();

  int
  _listen(int queue_size) const;

  int
  _accept(int (*handler)(int)) const;

  void
  _close() const;

};


#endif //SERVER_SOCKET_HH
