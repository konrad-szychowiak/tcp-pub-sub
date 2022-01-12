#include "Conversation.h"

void Conversation::add(Message message)
{
    base_of_messages.push_back(message);
    cout<<"Dodano"<<endl;
}

void Conversation::remove(Message message)
{
    for(int i=0; i<base_of_messages.size(); i++)
    {
        if(base_of_messages[i].id == message.id)
            base_of_messages.erase(base_of_messages.begin() + i);
            cout<<"Poprawnie usunieto"<<endl;
            break;
    }
}
