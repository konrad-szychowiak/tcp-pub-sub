#include "MessagesListener.h"

void MessagesListener::
update(Observable *observable)
{
  auto actual = (Conversation *) observable;
  /**
   * Generate a message to send via the socket
   * using a Visitor that scans a Conversation
   * and retrieves the last message posted in it.
   */
  auto messageGenerator = new MessagesVisitor();
  messageGenerator->visit((Visitable *) actual);
  message = move(messageGenerator->text);

  send();

  message = "";
  delete messageGenerator;
}
