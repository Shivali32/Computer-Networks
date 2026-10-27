#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "include/sans.h"
#include "include/rudp.h"
#include "include/soc_def.h"
#define BUFF_LEN 1024


int sans_send_pkt(int socket, const char* buf, int len) {
  struct sockaddr *address;
  socklen_t addr_len;
  int seqnum;
  for (size_t i = 0; i <  MAX_SOCKETS; i++) {
    if (sock_info[i].socket_id == socket) {
        address = sock_info[i].address;
        addr_len = sock_info[i].addr_len;
        seqnum = sock_info[i].seqnum;
        sock_info[i].seqnum++;
        break;
    }
  }
  rudp_packet_t *packet = malloc(sizeof(rudp_packet_t) + len);
  packet->type = DAT;
  packet->seqnum = seqnum;
  memcpy(packet->payload, buf, len);
  int bytes_sent;
  while(1) {
    struct timeval timeout = { .tv_usec = 20000 };
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    bytes_sent = sendto(socket, packet, sizeof(rudp_packet_t) + len, 0, address, addr_len);
    rudp_packet_t response;
    int rcvd_bytes = recvfrom(socket, &response, sizeof(response), 0, address, &addr_len);
    if (rcvd_bytes > 0 && (response.type & ACK) && response.seqnum == seqnum) {
      break;
    }
  }
  return bytes_sent;
}

int sans_recv_pkt(int socket, char* buf, int len) {
  struct sockaddr *address;
  socklen_t addr_len;
  int seqnum;
  for (size_t i = 0; i <  MAX_SOCKETS; i++) {
    if (sock_info[i].socket_id == socket) {
        address = sock_info[i].address;
        addr_len = sock_info[i].addr_len;
        seqnum = sock_info[i].seqnum;
        sock_info[i].seqnum++;
        break;
    }
  }
  rudp_packet_t *response = malloc(sizeof(rudp_packet_t) + BUFF_LEN);
  int rcvd_bytes = recvfrom(socket, response, sizeof(rudp_packet_t) + BUFF_LEN, 0, address, &addr_len);
  while(rcvd_bytes < 0 || response->type & DAT || response->seqnum != seqnum) {
    rcvd_bytes = recvfrom(socket, response, sizeof(rudp_packet_t) + BUFF_LEN, 0, address, &addr_len);
  }
  rudp_packet_t *ack_packet = malloc(sizeof(rudp_packet_t));
  ack_packet->type = ACK;
  ack_packet->seqnum = response->seqnum;
  sendto(socket, ack_packet, sizeof(rudp_packet_t), 0, address, addr_len);
  int payload_len = rcvd_bytes - sizeof(rudp_packet_t);
  memcpy(buf, response->payload, payload_len);
  buf[payload_len] = '\0';
  return payload_len;
}
