#include <sys/types.h>
#include <sys/socket.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "include/rudp.h" 
#include "include/sans.h" 
#include "include/soc_def.h"



int sans_send_pkt(int socket, const char* buf, int len) {

struct addrinfo conn_pres = socket_details[socket];

    ssize_t sent_bytes = sendto(socket, buf, len, 0, (struct sockaddr*)conn_pres.ai_addr, conn_pres.ai_addrlen);
    if (sent_bytes == -1) {
        return -1;
    }
    return (int)sent_bytes;
}
int sans_recv_pkt(int socket, char* buf, int len) {
    ssize_t bytes_received;
    struct addrinfo conn_pres = socket_details[socket];
    bytes_received = recvfrom(socket, buf, len, 0, (struct sockaddr*)conn_pres.ai_addr, &conn_pres.ai_addrlen);

    if (bytes_received < 0) {
        return -1;
    }

    return (int)bytes_received;
}
