#include <unistd.h>
#include <cstring>
#include "Listener.h"
#include "../mutex.hh"

void Listener::send()
{
  const char *answer = message.c_str();
  cout << answer << endl;
  lock(writeAccess);
  write(connectionSocket, answer, strlen(answer) + 1);
  unlock(writeAccess);
}

void Listener::update(Observable *observable)
{
  cout << "[log:" << connectionSocket << "] I have been updated\n";
  send();
}