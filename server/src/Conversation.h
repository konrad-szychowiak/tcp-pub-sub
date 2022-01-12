#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <deque>
#include <algorithm>
#include <stdio.h>
#include "Message.h"
#include "abstract/Visitable.h"
#include "abstract/Notifier.h"

using namespace std;

class Conversation : public Notifier, Visitable
{
public:
    deque <Message> base_of_messages;
    string author;
    int id;

    void add(Message message);
    void remove(Message message);
};
