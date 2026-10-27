#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "include/sans.h"

#define MAX_BUFFER 1024

int smtp_agent(const char* host, int port) {

    char email[256], path[256];
    char response[MAX_BUFFER];
    int socket, rcvd_pkt;
    int protocol = IPPROTO_TCP;
    FILE *email_file;

    scanf("%255s %255s", email, path);

    socket = sans_connect(host, port, protocol);
    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        // printf("%s", response);
    }

    snprintf(response, sizeof(response), "HELO %s\r\n", email);
    sans_send_pkt(socket, response, strlen(response));

    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    snprintf(response, sizeof(response), "MAIL FROM: <%s>\r\n", email);
    sans_send_pkt(socket, response, strlen(response));

    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    snprintf(response, sizeof(response), "RCPT TO: <%s>\r\n", email);
    sans_send_pkt(socket, response, strlen(response));

    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    snprintf(response, sizeof(response), "DATA\r\n");
    sans_send_pkt(socket, response, strlen(response));

    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    email_file = fopen(path, "r");        
    while (fgets(response, sizeof(response), email_file)) {
        sans_send_pkt(socket, response, strlen(response));
    }
    fclose(email_file);

    snprintf(response, sizeof(response), "\r\n.\r\n");
    sans_send_pkt(socket, response, strlen(response));

    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }
    
    snprintf(response, sizeof(response), "QUIT\r\n");
    sans_send_pkt(socket, response, strlen(response));
    
    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }
    
    sans_disconnect(socket);

    return 0;
}
