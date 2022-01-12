#include <iostream>
#include "../abstract/Listener.h"

using namespace std;

class ConversationsListener : public Listener
{
public:
  explicit ConversationsListener(int connectionSocketDescriptor) : Listener(connectionSocketDescriptor)
  {}
};

