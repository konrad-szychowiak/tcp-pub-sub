#pragma once
#include <iostream>
#include "Observable.hh"
//#include "Notifier.h"

using namespace std;

class Listener
{
public:
    int connectionSocket;

    Listener(int socketDescriptor) : connectionSocket(socketDescriptor) {}

    void update(Observable *observable);

    void send();
};

