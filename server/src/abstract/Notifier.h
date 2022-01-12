#pragma once
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "Listener.h"

using namespace std;

class Notifier
{
  vector<Listener*> listeners;

public:
  void
  addListener(Listener *listener);

  void
  removeListener(Listener *listener);
//
//  void
//  notifyAll();
};

