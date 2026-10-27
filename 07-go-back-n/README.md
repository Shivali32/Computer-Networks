# Project 7: Driver and Go-Back-N

This project moves packet transmission from the application call into a background transport worker and extends Stop and Wait into Go-Back-N. The send function creates a packet and adds it to a ring buffer. The worker processes the send window, transmits pending packets, receives acknowledgements, and removes acknowledged entries. If an acknowledgement times out, the pending window is sent again. The assignment examines how an application can hand data to a transport queue while a separate worker manages the packet exchange.

## Main Steps

- Create data packets with sequence numbers and queue them in the send window.
- Use a ring buffer to track queued packets and their socket identifiers.
- Transmit the pending window from the backend worker.
- Match acknowledgements to the packets awaiting confirmation and release completed entries.
- Resend pending packets after a timeout and continue receiving and acknowledging data.

## Files

- [p7-sans_backend.c](p7-sans_backend.c): the ring buffer, enqueue and dequeue helpers, and backend send-and-acknowledgement loop.
- [p7-sans_transport.c](p7-sans_transport.c): packet creation, queue insertion, data receipt, and acknowledgements.
- [p7-sans_socket.c](p7-sans_socket.c): TCP and RUDP connection functions and socket-map entries.
- [p7-soc_def.h](p7-soc_def.h) and [p7-socket_map.h](p7-socket_map.h): connection-map and sequence-state declarations.
- [p7_tests.c](p7_tests.c): course tests for single and multiple queued packets, retransmission, and acknowledgement behavior.
- [assignment.md](assignment.md): the complete backend-driver and Go-Back-N requirements.
