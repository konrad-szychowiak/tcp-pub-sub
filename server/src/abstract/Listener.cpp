#include <unistd.h>
#include <cstring>
#include "Listener.h"
//#include "Notifier.h"

void Listener::send()
{
//  cout << "[log:" << connectionSocket << "] writing from here\n";
}

void Listener::update(Observable *observable)
{
  cout << "[log:" << connectionSocket << "] I have been updated\n";
  send();
}
