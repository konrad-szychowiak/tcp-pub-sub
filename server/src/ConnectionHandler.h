#include <iostream>
#include <map>
#include <deque>
#include "abstract/Listener.h"

using namespace std;

class ConnectionHandler
{
    int connectionSocket;
    map<int, Listener> createdListeners;
    deque <int> createdConversations;

    void closeConnection();
    void read();
};
