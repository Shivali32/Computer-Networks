# Project 6: Stop and Wait

This project adds reliable packet transfer to the UDP connection through Stop and Wait. The sender attaches a sequence number to a data packet and waits for the acknowledgement with that number before proceeding. A receive timeout or an unexpected acknowledgement leads to another transmission of the packet. The receiving side examines packet sequence numbers and sends acknowledgements, linking the application's send and receive calls to the state of the packet exchange.

## Main Steps

- Keep connection and sequence information for each socket.
- Build a data packet from the caller's buffer and sequence number.
- Send the packet and wait for the matching acknowledgement.
- Retry after a timeout or an incorrect acknowledgement.
- Receive data packets and acknowledge the expected sequence.

## Files

- [p6-sans_socket_6.c](p6-sans_socket_6.c): connection setup, peer addresses, and per-socket sequence state.
- [p6-sans_transport_6.c](p6-sans_transport_6.c): the Stop-and-Wait send and receive routines.
- [p6_tests.c](p6_tests.c): course tests covering payloads, sequence numbers, timeouts, duplicate packets, and out-of-order acknowledgements.
- [assignment.md](assignment.md): the detailed reliability requirements.

This assignment builds on the [RUDP handshake](../05-rudp-handshake/) and its [packet definition](../05-rudp-handshake/include/rudp.h). Project 7 extends the one-packet exchange into a send window managed by a background worker.
