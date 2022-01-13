#include "ConversationsListener.h"

void ConversationsListener::
update(Observable *observable)
{
  auto actual = (ConversationsManager *) observable;
  /**
   * Generate a message to send via the socket
   * using a Visitor that scans the ConversationManager
   * and retrieves a list of all conversations.
   */
  auto messageGenerator = new ConversationsVisitor();
  messageGenerator->visit((Visitable *) actual);
  message = messageGenerator->text;

  send();

  message = "";
  delete messageGenerator;
}
