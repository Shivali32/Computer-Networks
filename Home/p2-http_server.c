
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/sans.h"

#define MAX_BUFFER 1024

int http_server(const char* host, int port) {

    int protocol = IPPROTO_TCP;
    int socket = sans_accept(host, port, protocol);

    char response[MAX_BUFFER];

    int rcvd_bytes = sans_recv_pkt(socket, response, MAX_BUFFER - 1);
    response[rcvd_bytes] = '\0';

    char method[8], path[256];
    // scanf("%7s %255s", method, path);
    // printf("%s, %s", method, path);
    sscanf(response, "%7s /%255s", method, path);

    size_t file_size;
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    char *file_content = (char *)malloc(file_size);
    fread(file_content, 1, file_size, file);
    fclose(file);

    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: %zu\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n", file_size);

    sans_send_pkt(socket, response, strlen(response));

    for (size_t tot_bytes = 0; tot_bytes < file_size; tot_bytes += MAX_BUFFER) {
        size_t tot_send = MAX_BUFFER;
        if (file_size - tot_bytes < MAX_BUFFER) {
            tot_send = file_size - tot_bytes;
        }
        sans_send_pkt(socket, file_content + tot_bytes, tot_send);
    }


    free(file_content);
    sans_disconnect(socket);

    return 0;
}