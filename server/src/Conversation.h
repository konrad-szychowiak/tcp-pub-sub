#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <deque>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include "Message.h"
#include "abstract/visiting.h"
#include "abstract/Notifier.h"

using namespace std;

class Conversation : public Notifier, Visitable
{
public:
  Message *last_message = nullptr;
  string name;
  string uuid;
  int id = -1;

  Conversation(string name, string uuid) : name(move(name)), uuid(move(uuid))
  {}

  explicit Conversation(string name) : name(move(name))
  {
    this->uuid = this->name + "-uuid";
  }

  void add(Message *message);

  void remove(Message message);
};
