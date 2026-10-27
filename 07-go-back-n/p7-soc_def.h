#ifndef SOC_DEF_H
#define SOC_DEF_H

// #include <netdb.h>

// #define MAX_SOCKETS 10
// #define MAX_CONNECTIONS 10
// extern struct addrinfo socket_details[MAX_SOCKETS];


// typedef struct {
//     int socket_id;            
//     socklen_t addr_len;      
//     struct sockaddr *address;
//     int seqnum;              
// } socket_entry_t;

// extern socket_entry_t sock_info[MAX_SOCKETS];

// #endif


#include <netinet/in.h>
#include <stddef.h>
#define MAX_SOCKET_COUNT 10

typedef struct {
    int socket_id;
    struct sockaddr *address;
    socklen_t addr_len;
    int seqnum;
} socket_entry_t;

extern socket_entry_t socket_map[MAX_SOCKET_COUNT];