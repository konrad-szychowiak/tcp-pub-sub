#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <deque>
#include <stdio.h>

using namespace std;

class Message
{
public:
    int id;
    string author;
    string text;
    time_t rawtime;
    struct tm * timeinfo;
    char timestamp[20];

    Message(int id, string author, string text);
};

