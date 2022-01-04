#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include <iostream>
#include "server.hh"

#define SERVER_PORT 8080
#define QUEUE_SIZE 5

/**
 * @struct
 * struktura zawierająca dane, które zostaną przekazane do wątku
 */
struct thread_data_t
{
//TODO
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


int main(int argc, char *argv[])
{
  auto logger = new Logger(argv[0]);
  auto server = new Server(SERVER_PORT, QUEUE_SIZE, logger);

  while (server->handle(handleConnection))
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

  pthread_exit(NULL);
}

int handleConnection(int connection_socket_descriptor)
{
  //wynik funkcji tworzącej wątek
  int create_result = 0;

  const char *answer = "Hello, world!";

  write(connection_socket_descriptor, answer, strlen(answer));
  std::cout << answer << std::endl;

  //uchwyt na wątek
//  pthread_t thread1;

  //dane, które zostaną przekazane do wątku
  //TODO dynamiczne utworzenie instancji struktury thread_data_t o nazwie t_data (+ w odpowiednim miejscu zwolnienie pamięci)
  //TODO wypełnienie pól struktury

//  create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)t_data);
//  if (create_result){
//    printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
//    exit(-1);
//  }

  //TODO (przy zadaniu 1) odbieranie -> wyświetlanie albo klawiatura -> wysyłanie
  return 1;
}