#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../abstract/Listener.h"
#include "../ConversationsManager.h"
#include "../visitors/ConversationsVisitor.h"

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T *)
{
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
  override;
};