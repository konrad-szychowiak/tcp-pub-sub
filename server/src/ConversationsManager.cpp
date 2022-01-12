#include "ConversationsManager.h"

void ConversationsManager::addConversation(Conversation *conversation)
{
  conversation->id = newConversationId;
  conversations.insert({newConversationId, conversation});
  newConversationId++;
}

void ConversationsManager::removeConversationById(int id)
{
  conversations.erase(id);
}

Conversation *ConversationsManager::getConversationById(int id)
{
  return conversations[id];
}
