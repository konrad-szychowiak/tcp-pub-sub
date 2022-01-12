#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include "ConversationsManager.h"

using namespace std;

int main()
{
    int id = 0;
    Message wiadomosc(id++, "Janek", "Hello world and others");
    Conversation konwersacja;
    Conversation konwersacja2;
    ConversationsManager manager;
    manager.addConversation(konwersacja);
    manager.addConversation(konwersacja2);
    manager.removeConversationById(0);
    manager.getConversationById(1);
    return 0;
}
