//
// Created by konrad on 13.01.2022.
//

#ifndef SERVER_MUTEX_HH
#define SERVER_MUTEX_HH

#include <thread>

#define lock(sem) pthread_mutex_lock(&sem)
#define unlock(sem) pthread_mutex_unlock(&sem)

typedef pthread_mutex_t Mutex;

/**
 * Guards access to any call to write() on connection sockets
 */
Mutex writeAccess = PTHREAD_MUTEX_INITIALIZER;

// fixme
// Mutex clientsCountAccess = PTHREAD_MUTEX_INITIALIZER;

#endif //SERVER_MUTEX_HH
