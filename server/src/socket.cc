//
// Created by konrad on 27.12.2021.
//

#include "socket.hh"

int Socket::
_init(int port)
{
  char reuse_addr_val = 1;

  memset(&server_address, 0, sizeof(struct sockaddr));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);

  server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket_descriptor < 0)
  {
    fprintf(stderr, "Błąd przy próbie utworzenia gniazda..\n");
    exit(1);
  }
  setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse_addr_val, sizeof(reuse_addr_val));

  return server_socket_descriptor;
}

int Socket::
_bind()
{
  int bind_result = bind(server_socket_descriptor, (struct sockaddr *) &server_address, sizeof(struct sockaddr));
  if (bind_result < 0)
  {
    fprintf(stderr, "Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n");
    exit(1);
  }
  return bind_result;
}

int Socket::
_listen(int queue_size) const
{
  int listen_result = listen(server_socket_descriptor, queue_size);
  if (listen_result < 0)
  {
    fprintf(stderr, "Błąd przy próbie ustawienia wielkości kolejki.\n");
    exit(1);
  }
  return listen_result;
}

int Socket::
_accept(int (*handler)(int)) const
{
  int connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
  if (connection_socket_descriptor < 0)
  {
    fprintf(stderr, "Błąd przy próbie utworzenia gniazda dla połączenia.\n");
    exit(1);
  }

  return handler(connection_socket_descriptor);
}

void Socket::
_close() const
{
  close(server_socket_descriptor);
}
