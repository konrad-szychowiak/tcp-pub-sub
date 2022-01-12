#include <unistd.h>
#include <cstring>
#include "Listener.h"
//#include "Notifier.h"

void Listener::send()
{
  const char *answer = "Hello from a listener!";
  cout << "[log:" << connectionSocket << "] writing from here\n";
  write(connectionSocket, answer, strlen(answer)+1);
}

void Listener::update(Observable *observable)
{
  cout << "[log:" << connectionSocket << "] I have been updated\n";
  send();
}
