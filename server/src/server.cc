//
// Created by konrad on 27.12.2021.
//

#include "server.hh"

Server::Server(int port, int queue_size, Logger *logger) : logger(logger)
{
  this->socket = new Socket();
  socket->_init(port);
  socket->_bind();
  socket->_listen(queue_size);

  char info[30] = {};
  snprintf(info, 30, "Server listening on: %d", port);
  logger->log(info);
}

Server::~Server()
{
  socket->_close();
  delete this->socket;
}

int Server::connection(int (&connection_handler)(int))
{
  return socket->_accept(&connection_handler);
}
