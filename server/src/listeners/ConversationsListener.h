#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../abstract/Listener.h"
#include "../ConversationsManager.h"

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
  return is_base_of<Base, T>::value;
}

class ConversationsListener : public Listener
{
public:
  explicit
  ConversationsListener(int connectionSocketDescriptor)
      : Listener(connectionSocketDescriptor)
  {}

  void
  update(Observable *observable)
  override {
    auto actual = (ConversationsManager*) observable;
    for (auto p : actual->conversations)
    {
      message += "\t" + to_string(p.first);
      message += "\t" + (*p.second).name;
      message += "\t" + (*p.second).uuid;
    }
    send();
  }

  void
  send()
  override
  {
//    Listener::send();
    message = 'L' + message + ";";
    const char *answer = message.c_str();
    cout << answer << endl;
    write(connectionSocket, answer, strlen(answer) + 1);
    message = "";
  }
};