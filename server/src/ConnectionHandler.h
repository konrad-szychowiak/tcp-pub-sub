#include <iostream>
#include <map>
#include <deque>
#include "abstract/Listener.h"

using namespace std;

class ConnectionHandler
{
  int connectionSocket;
  map<int, Listener> createdListeners;
  deque<int> createdConversations;

public:
  /**
   *
   * @param socket  socket descriptor of the socket created for the connection handled by this instance
   */
  ConnectionHandler(int socket) : connectionSocket(socket)
  {}

  void closeConnection();

  void read();
};
