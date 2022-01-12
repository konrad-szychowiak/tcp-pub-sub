#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <iostream>
#include "server.hh"
#include "abstract/Notifier.h"
#include "abstract/Listener.h"
#include "ConversationsManager.h"
#include "listeners/ConversationsListener.h"
#include "ConnectionHandler.h"

#define SERVER_PORT 8080
#define QUEUE_SIZE 5

/**
 * @struct
 * struktura zawierająca dane, które zostaną przekazane do wątku
 */
struct thread_data_t
{
  int connection_socket_descriptor;

};

/**
 * Funkcja opisującą zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
 * @param t_data
 */
void *ThreadBehavior(void *t_data);

int connectionHandlerFactory(int connection_socket_descriptor);

ConversationsManager state;
//Notifier no = Notifier();

int main(int argc, char *argv[])
{

  cout << "\n";

  auto logger = new Logger(argv[0]);
  auto server = new Server(SERVER_PORT, QUEUE_SIZE, logger);

  while (server->connection(connectionHandlerFactory))
  {}

  delete server;
  delete logger;

  return (0);
}


void *ThreadBehavior(void *t_data)
{
  pthread_detach(pthread_self());
  struct thread_data_t *th_data = (struct thread_data_t *) t_data;

  auto sd = (*th_data).connection_socket_descriptor;

  // before read //
  cout << "[log] socket descriptor is {" << sd << "}\n";

  /**
   * Create listener that awaits updates about the list of conversations
   */
  auto conversationsListener = new ConversationsListener(sd);

  const char *answer = "Hello, world!\n";
  write(sd, answer, strlen(answer)+1);

  // FIXME access via mutex
  state.addListener(conversationsListener);
  sleep(5);
  state.notifyAll();

  // read
  char packSymbol;

  while(read(sd, &packSymbol, sizeof(char)) > 0)
  {
    cout << "[thread:" << sd << "] received: " << packSymbol << endl;
    switch (condition)
    {
      
    }
    state.addConversation()
  }

  cout << "[thread:" << sd << "] connection closed\n";

  // cleanup //

  state.removeListener(conversationsListener);
  delete conversationsListener;
  delete th_data;

  close(sd);

  pthread_exit(NULL);
}

/**
 * Funkcja obsługująca połączenie z nowym klientem.
 * @param connection_socket_descriptor
 * @returns 0 if continue, error code otherwise
 */
int connectionHandlerFactory(int connection_socket_descriptor)
{
  // uchwyt na wątek
  pthread_t connectionThread;
  // wynik funkcji tworzącej wątek
  int create_result = 0;


  //dane, które zostaną przekazane do wątku
  //TODO dynamiczne utworzenie instancji struktury thread_data_t o nazwie t_data (+ w odpowiednim miejscu zwolnienie pamięci)
  //TODO wypełnienie pól struktury

  auto t_data = new thread_data_t{connection_socket_descriptor};
  t_data->connection_socket_descriptor = connection_socket_descriptor;

  create_result = pthread_create(&connectionThread, NULL, ThreadBehavior, (void *) t_data);
  if (create_result)
  {
    printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
    exit(-1);
  }

  //TODO (przy zadaniu 1) odbieranie -> wyświetlanie albo klawiatura -> wysyłanie

//  pthread_join(connectionThread, NULL);

//


  return 1;
}