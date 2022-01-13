#include "MessagesVisitor.h"

void MessagesVisitor::visit(Visitable *visitable)
{
  auto conv = (Conversation*) visitable;
  auto msg = conv->last_message;
  text = "N\t" + to_string(conv->id) + '\t' + msg->text + ";";
}
