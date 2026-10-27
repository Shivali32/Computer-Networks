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

void enqueue_packet(int, rudp_packet_t*, int);
int get_sent();

int sans_send_pkt(int socket, const char* buf, int len) {
  int seqnum;
  for (size_t i = 0; i <  MAX_SOCKET_COUNT; i++) {
    if (socket_map[i].socket_id == socket) {
        seqnum = socket_map[i].seqnum;
        socket_map[i].seqnum++;
        break;
    }
  }
  rudp_packet_t *packet = malloc(sizeof(rudp_packet_t) + len);
  packet->type = DAT;
  packet->seqnum = seqnum;
  memcpy(packet->payload, buf, len);
  //int current_count = get_sent();
  //int target = current_count + 1;
  enqueue_packet(socket, packet, len);
  /*while(current_count != target) {
    current_count = get_sent();
  }*/
  return len;
}

int sans_recv_pkt(int socket, char* buf, int len) {
  struct sockaddr *address;
  socklen_t addr_len;
  int seqnum;
  for (size_t i = 0; i <  MAX_SOCKET_COUNT; i++) {
    if (socket_map[i].socket_id == socket) {
        address = socket_map[i].address;
        addr_len = socket_map[i].addr_len;
        seqnum = socket_map[i].seqnum;
        socket_map[i].seqnum++;
        break;
    }
  }
  rudp_packet_t *response = malloc(sizeof(rudp_packet_t) + BUFF_LEN);
  int bytes_received = recvfrom(socket, response, sizeof(rudp_packet_t) + BUFF_LEN, 0, address, &addr_len);
  while(bytes_received < 0 || response->type & DAT || response->seqnum != seqnum) {
    bytes_received = recvfrom(socket, response, sizeof(rudp_packet_t) + BUFF_LEN, 0, address, &addr_len);
  }
  rudp_packet_t *ack_packet = malloc(sizeof(rudp_packet_t));
  ack_packet->type = ACK;
  ack_packet->seqnum = response->seqnum;
  sendto(socket, ack_packet, sizeof(rudp_packet_t), 0, address, addr_len);
  int payload_len = bytes_received - sizeof(rudp_packet_t);
  memcpy(buf, response->payload, payload_len);
  buf[payload_len] = '\0';
  return payload_len;
}
