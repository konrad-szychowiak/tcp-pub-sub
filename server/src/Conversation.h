#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <deque>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include "Message.h"
#include "abstract/Visitable.h"
#include "abstract/Notifier.h"

using namespace std;

class Conversation : public Notifier, Visitable
{
public:
    deque <Message> base_of_messages;
    string name;
    int id = -1;

    explicit Conversation(string name) : name(std::move(name)) {}

    void add(Message message);
    void remove(Message message);
};
