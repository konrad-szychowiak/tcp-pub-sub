#pragma once
#include <iostream>

using namespace std;

class Visitable;

class Visitor
{
public:
    void visit(Visitable visitable);
};

class Visitable
{
public:
  void accept(Visitor visitor);
};

