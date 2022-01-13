#include <iostream>
#include "../abstract/visiting.h"

using namespace std;

class MessagesVisitor : public visiting
{
  void visit(Visitable *visitable) override {
    auto actual = (Message*) visitable;
    message = "N\t" + to_string(actual->id) + '\t' + actual->last_message->text + ";";
    send();
  }
};
