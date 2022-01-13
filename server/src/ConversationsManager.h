#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include "Conversation.h"
#include "abstract/Notifier.h"
#include "abstract/visiting.h"

using namespace std;

class ConversationsManager : public Notifier, Visitable
{
private:
    int newConversationId = 0;

public:
    map<int, Conversation*> conversations;

    void addConversation(Conversation* conversation);
    void removeConversationById(int id);
    Conversation *getConversationById(int id);
};
