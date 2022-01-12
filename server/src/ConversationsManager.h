#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include "Conversation.h"
#include "abstract/Notifier.h"
#include "abstract/Visitable.h"

using namespace std;

class ConversationsManager : public Notifier, Visitable
{
private:
    map<int, Conversation> conversations;
    int newConversationId = 0;

public:
    void addConversation(Conversation conversation);
    void removeConversationById(int id);
    Conversation getConversationById(int id);
};
