#pragma once

#include <iostream>
#include "Observable.hh"
//#include "Notifier.h"

using namespace std;

class Listener
{
protected:
  string message;

public:
  int connectionSocket;

  Listener(int socketDescriptor) : connectionSocket(socketDescriptor)
  {}

  virtual void update(Observable *observable);

  virtual void send();
};

