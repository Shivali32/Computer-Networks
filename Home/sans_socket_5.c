#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "include/rudp.h" 
#include "include/sans.h" 
#include "include/soc_def.h"

// #define PACKET_LENGTH 1400
#define USEC_TIME 20000  

struct addrinfo socket_details[MAX_SOCKETS];

    struct timeval timeout = {
    .tv_usec = USEC_TIME
    };

int rudp_connect(const char* hostname, int port, int protocol){
    
    struct addrinfo conn_info, *conn_add, *conn_pres;
    int re_socket_fd;
    char port_buffer[12] = {0};
    int pt;
    memset(&conn_info, 0, sizeof conn_info);
    conn_info.ai_family = AF_UNSPEC; 
    conn_info.ai_socktype = SOCK_DGRAM;
    if((pt = getaddrinfo(hostname, port_buffer, &conn_info, &conn_add)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(pt));
        return -1;
    }
    for(conn_pres = conn_add; conn_pres != NULL; conn_pres = conn_pres->ai_next){
        re_socket_fd = socket(conn_pres->ai_family, conn_pres->ai_socktype, conn_pres->ai_protocol);
        if(re_socket_fd == -1){
            continue;
        }
        break;
    }
    if(conn_pres == NULL){
        fprintf(stderr, "Failed to create UDP socket\n");
        freeaddrinfo(conn_add);
        return -1;
    }

    socket_details[re_socket_fd] = *conn_pres;
    
    if(setsockopt(re_socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0){
        close(re_socket_fd);
        freeaddrinfo(conn_add);
        return -1;
    }
    rudp_packet_t *send_packet = malloc(sizeof(rudp_packet_t));
    send_packet->type = SYN;
    send_packet->seqnum = 0;
    int total_length = sizeof(rudp_packet_t);
    int retry = 3;
    while(retry--){
    if (sans_send_pkt(re_socket_fd, (const char *)send_packet, total_length) == -1) {
        perror("Failed to send packet");
        free(send_packet);
        close(re_socket_fd);
        return -1;
    }
    char *buffer = malloc(total_length);
    int bytes_received = sans_recv_pkt(re_socket_fd, buffer, total_length);
    if (bytes_received == -1) {
        free(buffer);
        continue;
    }
    rudp_packet_t *recv_packet = (rudp_packet_t *)buffer;
    if( (recv_packet->type & SYN) && (recv_packet->type & ACK) ){
         free(buffer);
         free(send_packet);
            break;
        }
    }
    rudp_packet_t *send_packet_ack = malloc(sizeof(rudp_packet_t));
    send_packet_ack->type = ACK;
    send_packet_ack->seqnum = 0;
    if (sans_send_pkt(re_socket_fd, (const char *)send_packet_ack, total_length) == -1) {
        perror("Failed to send packet");
        free(send_packet);
        close(re_socket_fd);
        return -1;
    }
    free(send_packet_ack);
    return re_socket_fd;
}

int sans_connect(const char* hostname, int port, int protocol) {
  if(protocol != IPPROTO_TCP){
    return rudp_connect(hostname, port, protocol);
  }
  struct addrinfo conn_hnt, *conn_dets, *conn_pres;
  char port_buffer[12];
  int re_socket_fd = -1;

  memset(&conn_hnt, 0, sizeof(conn_hnt));
  conn_hnt.ai_family = AF_UNSPEC; 
  conn_hnt.ai_socktype = SOCK_STREAM; 

  snprintf(port_buffer, 11, "%d", port);
  getaddrinfo(hostname, port_buffer, &conn_hnt, &conn_dets);

  for(conn_pres = conn_dets; conn_pres != NULL; conn_pres = conn_pres->ai_next){
    re_socket_fd = socket(conn_pres->ai_family, conn_pres->ai_socktype, conn_pres->ai_protocol);
    if(re_socket_fd == -1) continue;
    if(connect(re_socket_fd, conn_pres->ai_addr, conn_pres->ai_addrlen) != -1){
        break;
    }
    close(re_socket_fd);
  }
  return re_socket_fd;
}

int rudp_accept(const char* address, int port, int protocol){


    struct addrinfo conn_info, *conn_add, *conn_pres;
    int re_socket_fd;
    char port_buffer[12];
    int pt;

    memset(&conn_info, 0, sizeof conn_info);
    conn_info.ai_family = AF_UNSPEC;
    conn_info.ai_socktype = SOCK_DGRAM;


    snprintf(port_buffer, sizeof(port_buffer), "%d", port);
    if((pt = getaddrinfo(address, port_buffer, &conn_info, &conn_add)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(pt));
        return -1;
    }

    for(conn_pres = conn_add; conn_pres != NULL; conn_pres = conn_pres->ai_next){
        re_socket_fd = socket(conn_pres->ai_family, conn_pres->ai_socktype, conn_pres->ai_protocol);
        if(re_socket_fd == -1){
            continue;
        }

        int opt = 1;
        if(setsockopt(re_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1){
            close(re_socket_fd);
            continue;
        }
        int w = bind(re_socket_fd, conn_pres->ai_addr, conn_pres->ai_addrlen);
        if(w == 0){
            break; 
        }

        close(re_socket_fd);
    }

    if(conn_pres == NULL){
        fprintf(stderr, "Failed to bind UDP socket\n");
        freeaddrinfo(conn_add);
        return -1;
    }

    if(setsockopt(re_socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0){
        close(re_socket_fd);
        freeaddrinfo(conn_add);
        return -1;
    }

    socket_details[re_socket_fd] = *conn_pres;
    int retry = 5;
    int total_length = sizeof(rudp_packet_t)+20;
    while(retry--){
         
    char *buffer = malloc(total_length);
        recvfrom(re_socket_fd, buffer, total_length, 0,(struct sockaddr*)conn_pres->ai_addr, &conn_pres->ai_addrlen);
        rudp_packet_t *recv_packet = (rudp_packet_t *)buffer;
    if( recv_packet->type != SYN ){
        free(buffer);
        continue;          
        }
        free(buffer);
        break;

    }


    retry = 2;
    rudp_packet_t *send_packet_syn_ack = malloc(sizeof(rudp_packet_t));
    send_packet_syn_ack->type = SYN|ACK;
    send_packet_syn_ack->seqnum = 0;
   
    while(retry--){
    if (sans_send_pkt(re_socket_fd, (const char *)send_packet_syn_ack, total_length) == -1) {
        perror("Failed to send packet");
        free(send_packet_syn_ack);
        close(re_socket_fd);
        return -1;
    }
    
    char *buffer = malloc(total_length);
    int bytes_received = recvfrom(re_socket_fd, buffer, total_length, 0,(struct sockaddr*)conn_pres->ai_addr, &conn_pres->ai_addrlen);
    if (bytes_received == -1) {
        free(buffer);
        continue;
    }
         free(buffer);
    }
     free(send_packet_syn_ack);
   return re_socket_fd;

    }

int sans_accept(const char* address, int port, int protocol) {
    if(protocol != IPPROTO_TCP){
        return rudp_accept(address, port, protocol);
    }
    struct addrinfo conn_hnt, *conn_dets, *conn_pres;
    int server_socket_fd = -1, client_socket_fd;
    char port_buffer[12];

    snprintf(port_buffer, 11, "%d", port);

    memset(&conn_hnt, 0, sizeof conn_hnt);
    conn_hnt.ai_family = AF_UNSPEC;
    conn_hnt.ai_socktype = SOCK_STREAM;
    conn_hnt.ai_flags = AI_PASSIVE;

    getaddrinfo(address, port_buffer, &conn_hnt, &conn_dets);

    for (conn_pres = conn_dets; conn_pres != NULL; conn_pres = conn_pres->ai_next) {
        server_socket_fd = socket(conn_pres->ai_family, conn_pres->ai_socktype, conn_pres->ai_protocol);
        if (server_socket_fd == -1) continue;

        int reuse_option = 1;
        setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_option, sizeof(reuse_option));

        if (bind(server_socket_fd, conn_pres->ai_addr, conn_pres->ai_addrlen) == 0) {
            if (listen(server_socket_fd, MAX_CONNECTIONS) == -1) {
                close(server_socket_fd);
                continue;
            }
            break; 
        }
        close(server_socket_fd); 
    }

    client_socket_fd = accept(server_socket_fd, NULL, NULL);
    if (client_socket_fd == -1) {
        close(server_socket_fd);
        return -1; 
    }
    return client_socket_fd; 
}

int sans_disconnect(int socket_fd) {
  return close(socket_fd);
}
