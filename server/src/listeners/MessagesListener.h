#include <iostream>
#include "../abstract/Listener.h"
#include "../Conversation.h"
#include "../visitors/MessagesVisitor.h"

using namespace std;

class MessagesListener : public Listener
{
public:
  Conversation *conversation = nullptr;

  explicit
  MessagesListener(int connectionSocketDescriptor)
      : Listener(connectionSocketDescriptor)
  {}

  void update(Observable *observable) override;
};
