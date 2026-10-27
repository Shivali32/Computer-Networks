# Project 5: RUDP Handshake

This project introduces connection setup for a custom Reliable UDP protocol. UDP carries datagrams without TCP's connection establishment, so the assignment adds a three-way handshake and records the remote address for later packet exchanges. The socket code contains separate paths for TCP and RUDP, while the transport functions send and receive datagrams using the peer information associated with the socket. This separates the connection procedure from the data-transfer functions used by the application code.

## Main Steps

- Create a UDP datagram socket for an RUDP connection.
- Exchange `SYN`, `SYN | ACK`, and `ACK` packets to establish the connection state.
- Use receive timeouts and retries during the handshake.
- Store the peer's address and address length for the connection.
- Send and receive data through `sendto` and `recvfrom`.

## Files

- [p5-sans_socket_5.c](p5-sans_socket_5.c): TCP and RUDP connection paths, handshake messages, and peer-address storage.
- [p5-sans_transport_5.c](p5-sans_transport_5.c): datagram transmission and receipt using the saved peer address.
- [include/rudp.h](include/rudp.h): the course packet flags and `rudp_packet_t` definition.
- [p5_tests.c](p5_tests.c): course tests for handshake order, timeouts, retransmission, and peer-address use.
- [p5-testing.h](p5-testing.h) and [p5-wrappers.c](p5-wrappers.c): the test definitions and function wrappers grouped with this assignment.
- [p5-test.txt](p5-test.txt): the accompanying test notes.
- [assignment.md](assignment.md): the full assignment requirements.
