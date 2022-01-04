//
// Created by konrad on 27.12.2021.
//

#ifndef SERVER_LOGGER_HH
#define SERVER_LOGGER_HH

#include <iostream>

class Logger
{
private:
  const char *who;

public:
  Logger(const char *author) : who(author)
  {}

  void error(const char *msg)
  {
    std::cerr << who << ": " << msg << std::endl;
  }

  void log(const char *msg)
  {
    std::cout << who << ": " << msg << std::endl;
  }
};


#endif //SERVER_LOGGER_HH
