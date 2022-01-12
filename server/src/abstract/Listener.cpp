#include <unistd.h>
#include <cstring>
#include "Listener.h"
//#include "Notifier.h"

void Listener::send()
{
  const char *answer = message.c_str();
  cout << answer << endl;
  write(connectionSocket, answer, strlen(answer) + 1);
}

void Listener::update(Observable *observable)
{
  cout << "[log:" << connectionSocket << "] I have been updated\n";
  send();
}
