#include <iostream>
#include "../abstract/visiting.h"
#include "../ConversationsManager.h"

using namespace std;

class ConversationsVisitor : public Visitor
{
public:
  void visit(Visitable *visitable);
};
