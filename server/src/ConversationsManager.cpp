#include "ConversationsManager.h"

void ConversationsManager::addConversation(Conversation conversation)
{
     conversations.insert({newConversationId, conversation});
     newConversationId++;
}

void ConversationsManager::removeConversationById(int id)
{
    conversations.erase(id);
}

Conversation ConversationsManager::getConversationById(int id)
{
    return conversations[id];
}
