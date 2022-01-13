//
// Created by konrad on 27.12.2021.
//

#ifndef SERVER_SERVER_HH
#define SERVER_SERVER_HH


#include "socket.hh"
#include "logger.hh"

class Server
{
private:
  Logger *logger;
  Socket *socket;

public:
  Server(int port, int queue_size, Logger* logger);

  ~Server();

  int connection(int(&connection_handler)(int));
};


#endif //SERVER_SERVER_HH
