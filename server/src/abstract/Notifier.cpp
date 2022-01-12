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

void Notifier::updateOne(Listener *listener)
{
  listener->update(this);
}

