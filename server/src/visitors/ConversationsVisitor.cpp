#include "ConversationsVisitor.h"

void ConversationsVisitor::
visit(Visitable *visitable)
{
  auto actual = (ConversationsManager*) visitable;
  for (auto p : actual->conversations)
  {
    text += "\t" + to_string(p.first);
    text += "\t" + (*p.second).name;
    text += "\t" + (*p.second).uuid;
  }
  text = 'L' + text + ";";
}
