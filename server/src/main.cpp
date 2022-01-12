#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <iostream>
#include "server.hh"
#include "abstract/Notifier.h"
#include "abstract/Listener.h"
#include "ConversationsManager.h"

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

/**
 * Funkcja obsługująca połączenie z nowym klientem.
 * @param connection_socket_descriptor
 * @returns 0 if continue, error code otherwise
 */
int handleConnection(int connection_socket_descriptor);

ConversationsManager state;
//Notifier no = Notifier();

int main(int argc, char *argv[])
{

  cout << "\n";

  auto logger = new Logger(argv[0]);
  auto server = new Server(SERVER_PORT, QUEUE_SIZE, logger);

  while (server->connection(handleConnection))
  {}

  delete server;
  delete logger;

  return (0);
}


void *ThreadBehavior(void *t_data)
{
  pthread_detach(pthread_self());
  struct thread_data_t *th_data = (struct thread_data_t *) t_data;
  //dostęp do pól struktury: (*th_data).pole
  //TODO (przy zadaniu 1) klawiatura -> wysyłanie albo odbieranie -> wyświetlanie

  auto sd = (*th_data).connection_socket_descriptor;

  /**
   * Create listener
   */
  auto l = new Listener();

  cout << "[log] socket descriptor is {" << sd << "}\n";

  const char *answer = "Hello, world!";
  write(sd, answer, strlen(answer));
//  std::cout << answer << std::endl;
  state.addListener(l);
  l->write();
  state.removeListener(l);

  delete l;

  pthread_exit(NULL);
}

int handleConnection(int connection_socket_descriptor)
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

  pthread_join(connectionThread, NULL);

  delete t_data;

  return 1;
}