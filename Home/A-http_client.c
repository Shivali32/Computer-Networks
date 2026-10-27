#include <netinet/in.h>
#include "include/sans.h"
#include<stdio.h>
//#include<conio.h>
#include<string.h>

int sans_connect(const char *hostname, int port, int protocol);
int sans_send_pkt(int socket_id, const char *buffer, int length);
int sans_recv_pkt(int socket_id, char *buffer, int length);
int sans_disconnect(int socket_id);


#define BUFFER_SIZE 1024

int http_client(const char *hostname, int port) {
    char method[16];
    char path[256];
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    int protocol = IPPROTO_TCP;
    int socket_id, bytes_sent, bytes_received;
    int total_received = 0;


    printf("Enter HTTP method : ");
    scanf("%15s", method);

    printf("Enter the path (without leading /): ");
    scanf("%255s", path);

    socket_id = sans_connect(hostname, port, protocol);
    if (socket_id < 0) {
        printf("Failed to connect to the server at %s:%d.\n", hostname, port);
        return -1;
    }

    snprintf(request, sizeof(request),
             "%s /%s HTTP/1.1\r\n"
             "Host: %s:%d\r\n"
             "User-Agent: sans/1.0\r\n"
             "Cache-Control: no-cache\r\n"
             "Connection: close\r\n"
             "Accept: /\r\n"
             "\r\n",
             method, path, hostname, port);

    bytes_sent = sans_send_pkt(socket_id, request, strlen(request));
    if (bytes_sent < 0) {
        printf("Failed to send the HTTP request.\n");
        sans_disconnect(socket_id);
        return -1;
    }

    do {
        bytes_received = sans_recv_pkt(socket_id, response, BUFFER_SIZE - 1);
        if (bytes_received < 0) {
            printf("Error receiving response.\n");
            break;
        }

        response[bytes_received] = '\0';

        printf("%s", response);

        total_received += bytes_received;
    } while (bytes_received > 0);

    sans_disconnect(socket_id);

    printf("\nTotal bytes received: %d\n", total_received);
}


// HTTP/1.1 200 OK
// Accept-Ranges: bytes
// Age: 556631
// Cache-Control: max-age=604800
// Content-Type: text/html; charset=UTF-8
// Date: Thu, 05 Sep 2024 05:00:59 GMT
// Etag: "3147526947"
// Expires: Thu, 12 Sep 2024 05:00:59 GMT
// Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
// Server: ECAcc (chd/07A8)
// Vary: Accept-Encoding
// X-Cache: HIT
// Content-Length: 1256
// Connection: close
