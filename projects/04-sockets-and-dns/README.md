# Project 4: Sockets and DNS

This project replaces the connection helpers used by the application assignments with TCP socket functions. Hostname resolution uses `getaddrinfo` to obtain candidate addresses, which are used to create and connect sockets or prepare a listening socket. The client and server paths expose the steps hidden behind the earlier SANS interface: resolving an address, creating a socket, establishing a connection, and closing its file descriptor.

## Main Steps

- Check that the requested transport protocol is TCP.
- Convert the hostname and port into address information with `getaddrinfo`.
- Try candidate addresses and create sockets using their family, type, and protocol.
- Use `connect` for a client connection or `bind`, `listen`, and `accept` for a server connection.
- Close the connection through `sans_disconnect`.

## Files

- [p4-sans_socket_4.c](p4-sans_socket_4.c): the implementations of `sans_connect`, `sans_accept`, and `sans_disconnect`.
- [p4_tests.c](p4_tests.c): course tests for address resolution, socket arguments, call order, and failure paths.
- [assignment.md](assignment.md): the full connection-management requirements.

The HTTP and SMTP assignments call these connection functions through the [SANS interface](../../miscellaneous/shimate-main/src/include/sans.h). Projects 5 through 7 extend this connection model with UDP and transport state.
