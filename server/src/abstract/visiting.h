#pragma once

#include <iostream>

using namespace std;

class Visitable;

class Visitor
{
public:
  string text;

  void visit(Visitable visitable);
};

class Visitable
{
public:
  [[maybe_unused]] void accept(Visitor visitor);
};

