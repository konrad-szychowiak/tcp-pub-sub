#include <unistd.h>
#include <string>
#include <pthread.h>
#include <iostream>
#include "server.hh"
#include "abstract/Notifier.h"
#include "ConversationsManager.h"
#include "listeners/ConversationsListener.h"
#include "listeners/MessagesListener.h"

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
 * Data about all the active conversations on the server.
 */
ConversationsManager state;

// fixme
//int clientCounter;


void *ThreadBehavior(void *t_data);
int connectionHandlerFactory(int connection_socket_descriptor);


int main(int argc, char *argv[])
{

//  cout << "\n";

  auto logger = new Logger(argv[0]);
  auto server = new Server(SERVER_PORT, QUEUE_SIZE, logger);


//  auto hello = new Conversation("Hello");
//  state.addConversation(hello);
//
//  auto world = new Conversation("World");
//  state.addConversation(world);
//
//  auto ala = new Conversation("Ala ma kota");
//  state.addConversation(ala);


  while (server->connection(connectionHandlerFactory))
  {}

  delete server;
  delete logger;

  return (0);
}

/**
 * Funkcja opisującą zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
 * @param t_data
 */
void *ThreadBehavior(void *t_data)
{
  // after create //

  pthread_detach(pthread_self());
  auto *th_data = (struct thread_data_t *) t_data;
  auto sd = (*th_data).connection_socket_descriptor;

  vector<Conversation *> createdConversations;
  map<int, MessagesListener *> createdListeners;


  // before read //

  /**
   * Create listener that awaits updates about the list of conversations
   */
  auto conversationsListener = new ConversationsListener(sd);
  /**
   * Listen for changes in the list of conversations
   */
  state.addListener(conversationsListener);
  /**
   * Send the up-to-date list of conversations to the connected client
   */
  state.notifyOne(conversationsListener);

  // log //
  cout << "[log:" << sd << "] new connection established and ready\n";

  // read //
  char packSymbol;
  string fullMessage;

  while (read(sd, &packSymbol, sizeof(char)) > 0)
  {
    /**
     * assemble incoming data character by character
     */
    if (packSymbol == ';')
    {
      char initial = fullMessage.at(0);
      switch (initial)
      {
        /**
         * Create a new conversation
         * @param name name of the conversation
         * @param uuid unique identifier for the sake of clients
         */
        case 'C':
        {
          string withoutSymbol = fullMessage.substr(2);
          int dividerPosition = withoutSymbol.find('\t');

          string name = withoutSymbol.substr(0, dividerPosition);
          string uuid = withoutSymbol.substr(dividerPosition + 1);

          cout << "[log:" << sd << "] create a new conversation :: " << name << " :: " << uuid << endl;

          auto myNewConversation = new Conversation(name, uuid);
          createdConversations.push_back(myNewConversation);
          state.addConversation(myNewConversation);
          state.notifyAll();

          auto createdConversationListener = new MessagesListener(sd);
          auto convo = state.getConversationById(myNewConversation->id);
          convo->addListener(createdConversationListener);
          createdConversationListener->conversation = convo;
          createdListeners.insert({convo->id, createdConversationListener});

          break;
        }
        /**
         * Delete a conversation
         * @param id
         */
        case 'D':
        {
          string strID = fullMessage.substr(2);
          int id = atoi(strID.c_str());
          cout << "deleting an old conversation: " << strID << " \n";
          state.removeConversationById(id);
          state.notifyAll();

          break;
        }
          /**
           * Subscribe to an existing conversation
           * @param id ID of the target conversation
           */
        case 'S': // Subscribe to an existing conversation
        {
          string strID = fullMessage.substr(2);
          int id = atoi(strID.c_str());
          auto subscribedConversationListener = new MessagesListener(sd);
          auto convo = state.getConversationById(id);
          convo->addListener(subscribedConversationListener);
          subscribedConversationListener->conversation = convo;
          createdListeners.insert({convo->id, subscribedConversationListener});

          break;
        }
          /**
           * Unsubscribe
           * @param id ID of the target conversation
           */
        case 'U':
        {
          string strID = fullMessage.substr(2);
          int id = atoi(strID.c_str());

          cout << "[unsubscribe] to " << fullMessage << endl;

          /**
           * find a conversation by the given id
           */
          auto convo = state.getConversationById(id);
          /**
           * find the listener created for the given conversation
           */
          auto listener = createdListeners[id];
          /**
           * remove the listener from the conversations
           * AKA <i>unsubscribe</i>
           */
          convo->removeListener(listener);
          /**
           * remove entry about that listener from the collection of created listeners
           */
          createdListeners.erase(convo->id);
          /**
           * free the memory and delete the listener
           */
          delete listener;

          break;
        }
        /**
         * Post a new message
         * @param id
         * @param content text of the message
         */
        case 'P':
        {
          string withoutSymbol = fullMessage.substr(2);
          int dividerPosition = withoutSymbol.find('\t');
          string strID = withoutSymbol.substr(0, dividerPosition);
          int id = atoi(strID.c_str());
          string content = withoutSymbol.substr(dividerPosition + 1);
          cout << "post a msg in :: " << strID << " :with content: " << content << endl;

          auto targetConversation = state.getConversationById(id);
          targetConversation->add(new Message(0, "a", content));
          targetConversation->notifyAll();

          break;
        }
        default:
        {
          cerr << "[error] incomprehensible message from a client\n";
        }
      }
      fullMessage = "";
    }
    else
    {
      fullMessage += packSymbol;
    }
  }

  cout << "[log:" << sd << "] connection closed\n";

  // cleanup //

  for (auto pair: createdListeners)
  {
    auto listener = pair.second;
    auto convo = listener->conversation;
    if (convo != nullptr)
    { convo->removeListener(listener); }
    delete listener;
  }

  for (auto conversation: createdConversations)
  {
    state.removeConversationById(conversation->id);
    state.notifyAll();
    delete conversation;
  }

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
  /**
   * uchwyt na wątek
   */
  pthread_t connectionThread;

  auto t_data = new thread_data_t{connection_socket_descriptor};
  t_data->connection_socket_descriptor = connection_socket_descriptor;

  int create_result = pthread_create(&connectionThread, NULL, ThreadBehavior, (void *) t_data);
  if (create_result)
  {
    printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
    exit(-1);
  }

  return 1;
}