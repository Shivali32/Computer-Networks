#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_CONNECTIONS 10
#define PACKET_LENGTH 1400

int sans_connect(const char* hostname, int port, int protocol) {
  if(protocol != IPPROTO_TCP){
    return -1;
  }
  struct addrinfo connection_hints, *connection_info, *present;
  char re_port_buffer[12];
  int re_socket_fd = -1;

  memset(&connection_hints, 0, sizeof(connection_hints));
  connection_hints.ai_family = AF_UNSPEC; 
  connection_hints.ai_socktype = SOCK_STREAM; 

  snprintf(re_port_buffer, 11, "%d", port);
  getaddrinfo(hostname, re_port_buffer, &connection_hints, &connection_info);

  for(present = connection_info; present != NULL; present = present->ai_next){
    re_socket_fd = socket(present->ai_family, present->ai_socktype, present->ai_protocol);
    if(re_socket_fd == -1) continue;
    if(connect(re_socket_fd, present->ai_addr, present->ai_addrlen) != -1){
        break;
    }
    close(re_socket_fd);
  }
  return re_socket_fd;
}

int sans_accept(const char* address, int port, int protocol) {
    if(protocol != IPPROTO_TCP){
        return -1;
    }
    struct addrinfo connection_hints, *connection_info, *present;
    int server_re_socket_fd = -1, client_re_socket_fd;
    char re_port_buffer[12];

    snprintf(re_port_buffer, 11, "%d", port);

    memset(&connection_hints, 0, sizeof connection_hints);
    connection_hints.ai_family = AF_UNSPEC;
    connection_hints.ai_socktype = SOCK_STREAM;
    connection_hints.ai_flags = AI_PASSIVE;

    getaddrinfo(address, re_port_buffer, &connection_hints, &connection_info);

    for (present = connection_info; present != NULL; present = present->ai_next) {
        server_re_socket_fd = socket(present->ai_family, present->ai_socktype, present->ai_protocol);
        if (server_re_socket_fd == -1) continue;

        int reuse_option = 1;
        setsockopt(server_re_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_option, sizeof(reuse_option));

        if (bind(server_re_socket_fd, present->ai_addr, present->ai_addrlen) == 0) {
            if (listen(server_re_socket_fd, MAX_CONNECTIONS) == -1) {
                close(server_re_socket_fd);
                continue;
            }
            break; 
        }
        close(server_re_socket_fd); 
    }

    client_re_socket_fd = accept(server_re_socket_fd, NULL, NULL);
    if (client_re_socket_fd == -1) {
        close(server_re_socket_fd);
        return -1; 
    }
    return client_re_socket_fd; 
}

int sans_disconnect(int re_socket_fd) {
  return close(re_socket_fd);
}