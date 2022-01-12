#pragma once
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "Listener.h"

using namespace std;

class Notifier : public Observable
{
  vector<Listener*> listeners;

public:
  void
  addListener(Listener *listener);

  void
  removeListener(Listener *listener);

  void
  notifyAll();

  void notifyOne(Listener*listener);
};

