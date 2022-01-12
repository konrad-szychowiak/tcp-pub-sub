#include "Notifier.h"

void Notifier::addListener(Listener *listener)
{
  listeners.push_back(listener);
}

void Notifier::removeListener(Listener *listener)
{
  auto iterator = find(listeners.begin(), listeners.end(), listener);
  listeners.erase(iterator);
}

void Notifier::notifyAll()
{
  for ( auto listener : listeners )
  {
    listener->update(this);
  }
}

void Notifier::notifyOne(Listener *listener)
{
  cout << "not one\n";
  listener->update(this);
}

