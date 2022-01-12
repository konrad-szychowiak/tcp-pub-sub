#pragma once
#include "Visitor.h"

class Visitable
{
public:
    void accept(Visitor visitor);
};

