# Project 7: Driver and Go-Back-N

This project moves packet transmission into a background worker. The transport function queues packets in a ring buffer, and the backend sends pending packets, processes acknowledgements, and retries the window after a timeout.

## Contents

- `src/sans_backend.c`: the send window, queue helpers, and transport worker.
- `src/sans_transport.c`: packet creation, enqueueing, receiving, and acknowledgements.
- `src/sans_socket.c`: the latest saved TCP and RUDP connection functions.
- `include/soc_def.h`: the connection map and sequence-state declarations used by these versions.
- `variants/socket_map.h`: the separately saved, complete socket-map declaration file.
- `tests/p7_tests.c`: course tests for queued packets, retries, and acknowledgements.
- [requirements.md](requirements.md): the original project requirements.

## Current State

The saved `soc_def.h` has an unterminated include guard and prevents compilation as written. The course wiki also calls for an updated `sans.c` that starts the backend thread, but the available shared driver is the earlier version without that startup code. The Project 7 tests start their own worker thread.

These files preserve the Go-Back-N implementation attempt. A successful build and passing reliability tests have not been established. Shared packet definitions and course test utilities are in [shared support](../shared/README.md).
