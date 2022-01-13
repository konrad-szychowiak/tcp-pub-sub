#include <unistd.h>
#include <cstring>
#include "Listener.h"
#include "../mutex.hh"

/**
 * Send the message to the connection socket assigned to this Listener.
 *
 * <p>Sending is guarded by a mutex: <b>only one</b> Listener can write to a socket at a time to avoid mixing messages.</p>
 */
void Listener::send()
{
  const char *answer = this->message.c_str();
  cout << answer << endl;
  lock(writeAccess);
  write(this->connectionSocket, answer, strlen(answer) + 1);
  unlock(writeAccess);
}

/**
 * Update the Listener with data from an Observable object.
 *
 * Also sends the data via send() method.
 *
 * @param observable object to use for the update
 */
void Listener::update(Observable *observable)
{
  cout << "[log:" << connectionSocket << "] I have been updated\n";
  send();
}