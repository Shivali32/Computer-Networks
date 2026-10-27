# SANS Helper Library

Based on the helper-library page in the Fall 2024 course wiki. Early projects use `templates.a` to focus on application protocols before later projects replace socket and transport behavior.

- `sans_connect(host, port, protocol)` establishes a connection and returns a socket identifier.
- `sans_accept(iface, port, protocol)` waits for a peer and returns its socket identifier.
- `sans_send_pkt(socket, buffer, length)` transmits bytes on a connection and returns the number sent.
- `sans_recv_pkt(socket, buffer, length)` receives bytes into the supplied buffer and returns the number received, zero when no data is received, or a negative value on failure.
- `sans_disconnect(socket)` closes a connection.

The application stages use `IPPROTO_TCP`. The later RUDP stages add their own connection and reliability behavior over UDP. Function declarations are in [include/sans.h](include/sans.h).
