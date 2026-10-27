# Project 6: Stop and Wait

This project adds packet reliability to the UDP connection. The sender attaches a sequence number and retransmits until it receives the matching acknowledgement. The receiver checks packet order and sends acknowledgements for received data.

## Contents

- `src/sans_socket.c`: the saved `sans_socket_6.c` connection and sequence-state implementation.
- `src/sans_transport.c`: the saved `sans_transport_6.c` send and receive functions.
- `tests/p6_tests.c`: course tests for timeouts, sequence numbers, duplicate packets, and acknowledgements.
- [requirements.md](requirements.md): the original project requirements.

## Current State

These versions use `sock_info` and `MAX_SOCKETS` from an earlier `include/soc_def.h` that was not included in the repository. Project 7 instead uses `socket_map`, so its later header cannot be substituted directly.

The code is preserved as a course snapshot. Restoring the matching header and running the supplied tests are needed before claiming reliable delivery. Common packet definitions and test support are in [shared support](../shared/README.md).
