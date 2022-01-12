#include <iostream>
#include "../abstract/Listener.h"
#include "../Conversation.h"

using namespace std;

class MessagesListener : public Listener
{
public:
  explicit
  MessagesListener(int connectionSocketDescriptor)
      : Listener(connectionSocketDescriptor)
  {}

  void
  update(Observable *observable)
  override {
    auto actual = (Conversation*) observable;
    message = "N\t" + to_string(actual->id) + '\t' + actual->last_message->text + ";";
    send();
  }
};
