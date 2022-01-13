#include <iostream>
#include "../abstract/visiting.h"

using namespace std;

class ConversationsVisitor : public visiting
{
  void visit(Visitable *visitable) override {
    auto actual = (ConversationsManager*) visitable;
    for (auto p : actual->conversations)
    {
      message += "\t" + to_string(p.first);
      message += "\t" + (*p.second).name;
      message += "\t" + (*p.second).uuid;
    }
    message = 'L' + message + ";";
  }
}
