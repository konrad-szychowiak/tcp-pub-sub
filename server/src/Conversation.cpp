#include "Conversation.h"

void Conversation::add(Message *message)
{
  last_message = message;
  cout << "Dodano: " << message->text << endl;
}

void Conversation::remove(Message message)
{
//  for (int i = 0; i < base_of_messages.size(); i++)
//  {
//    if (base_of_messages[i].id == message.id)
//    {
//      base_of_messages.erase(base_of_messages.begin() + i);
//    }
//    cout << "Poprawnie usunieto" << endl;
//    break;
//  }
}

/**
 * @deprecated
 * @param name
 */
Conversation::Conversation(string name) : name(move(name))
{
  this->uuid = this->name + "-uuid";
}
