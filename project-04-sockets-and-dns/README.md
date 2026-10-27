# Project 4: Sockets and DNS

This project replaces the course library's TCP connection helpers with socket functions. It uses `getaddrinfo` to resolve a hostname, tries returned addresses, opens client or server connections, and closes sockets when finished.

## Contents

- `src/sans_socket.c`: the TCP-only version originally named `sans_socket_old1.c`.
- `tests/p4_tests.c`: course tests for address resolution, socket calls, and connection failures.
- [requirements.md](requirements.md): the original project requirements.

## Current State

The implementation passes a syntax check. It contains `sans_connect`, `sans_accept`, and `sans_disconnect`, and rejects protocols other than TCP. Error handling and address cleanup remain limited in this saved version.

This TCP-only file belongs here even though its old filename suggested a backup. The versions that add reliable UDP belong to Projects 5 through 7. See [shared support](../shared/README.md) for the common interface and test framework.
