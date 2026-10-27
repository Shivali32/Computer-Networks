
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

    scanf("%255s %255s", email, path);

    socket = sans_connect(host, port, protocol);

    size_t file_size;

    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    char *file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
    fclose(file);

    snprintf(response, sizeof(response), "HELO %s\r\n", email);
    sans_send_pkt(socket, response, strlen(response));

    // Receive server response for HELO
    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    snprintf(response, sizeof(response), "MAIL FROM: <%s>\r\n", email);
    sans_send_pkt(socket, response, strlen(response));

    // Receive server response for MAIL FROM
    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    // Step 3: Send RCPT TO command
    snprintf(response, sizeof(response), "RCPT TO: <%s>\r\n", email);
    sans_send_pkt(socket, response, strlen(response));

    // Receive server response for RCPT TO
    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }

    // Step 4: Send DATA command
    snprintf(response, sizeof(response), "DATA\r\n");
    sans_send_pkt(socket, response, strlen(response));

    // Receive server response for DATA
    rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER);
    if (rcvd_pkt > 0) {
        response[rcvd_pkt] = '\0';
        printf("%s", response);
    }