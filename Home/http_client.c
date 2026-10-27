#include <netinet/in.h>
#include "include/sans.h"
#include <stdio.h>
#include <string.h>

// #define MAX_BUFFER 1024

int http_client(const char* host, int port){
    
    char method[], path[256];

    char request[1024];
    char response[1024];
    int socket, rcvd_pkt;
    // int tot_pkt = 0;
    int protocol = IPPROTO_TCP;

    scanf("%7s %255s", method, path);

    socket = sans_connect(host, port, protocol);

    snprintf(request, sizeof(request),
        "%s /%s HTTP/1.1\r\n"
        "Host: %s:%d\r\n"
        "User-Agent: sans/1.0\r\n"
        "Cache-Control: no-cache\r\n"
        "Connection: close\r\n"
        "Accept: */*\r\n"
        "\r\n",
        method, path, host, port);
        
    sans_send_pkt(socket, request, 1024);

    // while((rcvd_pkt = sans_recv_pkt(socket, response, MAX_BUFFER - 1)) > 0){
    while((rcvd_pkt = sans_recv_pkt(socket, response, 1024)) > 0){
        response[rcvd_pkt] = '\0';
        printf ("%s", response);
        // tot_pkt = tot_pkt + rcvd_pkt;
        // if(tot_pkt > MAX_BUFFER){
        //     break;
        // }
    }
        
    sans_disconnect(socket);
    return 0;
}