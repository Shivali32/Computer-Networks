#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "include/rudp.h"
#include "include/soc_def.h"

#define SWND_SIZE 10
void populate_address(struct sockaddr **address, socklen_t *addr_len, int socket);

typedef struct {
  int socket;
  int packetlen;
  rudp_packet_t* packet;
} swnd_entry_t;

swnd_entry_t send_window[SWND_SIZE];  /*  Ring buffer containing the packets awaiting acknowledgement */

static int sent = 0;
static int count = 0;
static int head = 0;
static int rear = 0;

int get_sent() {
  return sent;
}

void populate_address(struct sockaddr **address, socklen_t *addr_len, int socket) {
  for (size_t i = 0; i <  MAX_SOCKET_COUNT; i++) {
    if (socket_map[i].socket_id == socket) {
        *address = socket_map[i].address;
        *addr_len = socket_map[i].addr_len;
        break;
    }
  }
}
/*
 * Helper: We recommend writing a helper function for pushing a packet onto the ring buffer
 *         that can be called from the main thread.
 *    (Remember to copy the packet to avoid thread conflicts!)
 */
void enqueue_packet(int sock, rudp_packet_t* pkt, int len) {
  rudp_packet_t *packet = malloc(sizeof(rudp_packet_t) + len);
  packet->type = pkt->type;
  packet->seqnum = pkt->seqnum;
  memcpy(packet->payload, pkt->payload, len);
  while(count - sent > SWND_SIZE);
  swnd_entry_t packet_entry;
  packet_entry.socket = sock;
  packet_entry.packetlen = sizeof(rudp_packet_t) + len;
  packet_entry.packet = packet;
  send_window[rear] = packet_entry;
  rear = (rear + 1) % SWND_SIZE;
  count = count + 1;
}

/*
 * Helper: We recommend writing a helper function for removing a completed packet from the ring
 *         buffer that can be called from the backend thread.
 */
static void dequeue_packet(void) {
  free(send_window[head].packet);
  sent = sent + 1;
  head = (head + 1) % SWND_SIZE;
}

/*  Asynchronous runner for the sans protocol driver.  This function  *
 *  is responsible for checking for packets in the `send_window` and  *
 *  handling the transmission of these packets in a reliable manner.  *
 *  (i.e. Stop-and-Wait or Go-Back-N)                                 */
void* sans_backend(void* unused) {
  
  while (1) {
    /* ---- Background worker code ---- */
    if(count - sent > 0) {
        int i = head;
        while (i != rear) {
          struct sockaddr *address;
          socklen_t addr_len;
          populate_address(&address, &addr_len, send_window[i].socket);
          sendto(send_window[i].socket, send_window[i].packet, send_window[i].packetlen, 0, address, addr_len);
          i = (i+1)%SWND_SIZE;
        }
        struct timeval timeout = { .tv_usec = 20000 };
        i = head;
        int curr_rear = rear;
        while (i != curr_rear) {
          struct sockaddr *address;
          socklen_t addr_len;
          populate_address(&address, &addr_len, send_window[i].socket);
          setsockopt(send_window[i].socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
          rudp_packet_t response;
          int bytes_received = recvfrom(send_window[i].socket, &response, sizeof(response), 0, address,&addr_len);
          if(bytes_received < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            break;
          }
          if(bytes_received > 0 && (response.type & ACK) && response.seqnum == send_window[i].packet->seqnum) {
            i = (i+1)%SWND_SIZE;
            dequeue_packet();
          }
        }
    }
    /*----------------------------------*/
  }

  return NULL;
}
