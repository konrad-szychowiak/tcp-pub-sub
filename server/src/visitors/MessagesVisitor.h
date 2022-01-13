#include <iostream>
#include "../abstract/visiting.h"
#include "../Message.h"
#include "../Conversation.h"

using namespace std;

class MessagesVisitor : public Visitor
{
public:
  void visit(Visitable *visitable);
};
