# Project 5: RUDP Handshake

This project adds connection setup over UDP through a three-way handshake. It exchanges `SYN`, `SYN | ACK`, and `ACK` packets, records the peer's address, and provides datagram send and receive functions while retaining TCP branches.

## Contents

- `src/sans_socket.c`: the saved `sans_socket_5.c` handshake and socket implementation.
- `src/sans_transport.c`: the saved `sans_transport_5.c` datagram functions.
- `tests/p5_tests.c`: course tests for handshakes, retries, and stored peer addresses.
- [requirements.md](requirements.md): the original assignment requirements.
- [RUDP handshake notes](../shared/rudp-handshake.md): flags and handshake sequence from the course wiki.

## Current State

Both files refer to an earlier `include/soc_def.h` with `MAX_SOCKETS`, `MAX_CONNECTIONS`, and `socket_details` declarations. That matching header was not present in the uploaded code. The later Project 7 header uses a different map and is not a replacement.

The RUDP packet definition is retained in [shared support](../shared/README.md). This snapshot needs its matching connection-state header before it can be built and tested.
