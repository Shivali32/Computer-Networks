# RUDP Handshake

Based on the handshake page in the Fall 2024 course wiki. The custom protocol carries state flags in the packet's `type` field.

- `DAT = 0`: a data packet.
- `SYN = 1`: a synchronization request.
- `ACK = 2`: an acknowledgement.
- `FIN = 4`: a request to end the stream.

Flags such as `SYN` and `ACK` can be combined with a bitwise OR. The packet definition is in [include/rudp.h](include/rudp.h).

The connecting side sends `SYN`, waits for `SYN | ACK`, saves the peer address, and sends `ACK`. The accepting side waits for `SYN`, saves the sender's address, sends `SYN | ACK`, and waits for the final `ACK`.

The course specifies a 20 millisecond receive timeout for handshake retransmissions, configured using `SO_RCVTIMEO`. A timeout causes the sender to retry the handshake packet.
