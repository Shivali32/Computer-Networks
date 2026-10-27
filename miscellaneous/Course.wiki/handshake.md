# Handshake

In order to setup the state necessary for connection-based data streams, reliable protocols need to perform some sort of connection establishment routine, usually called a _Handshake_.  For our RUDP protocol, we will be implementing the most basic version of the same Handshake used by TCP.

## State Bits

The handshake is tracked by each side using flag bits inside the header.  We will be using the provided <code>rudp_packet_t</code> struct, which includes a <code>.type</code> field to encode any state bits.

## RUDP Type Field

<table>
  <tr>
    <th>Macro</th><th>Value</th><th>Meaning</th>
  </tr>
  <tr>
    <td>DAT</td><td>0</td><td>Packet contains only data in the payload</td>
  </tr>
  <tr>
    <td>SYN</td><td>1</td><td>Packet is part of the synchronization (handshake) procedure</td>
  </tr>
  <tr>
    <td>ACK</td><td>2</td><td>Packet is acknowledging a previous packet</td>
  </tr>
  <tr>
    <td>FIN</td><td>4</td><td>Packet is requesting the termination of the data stream</td>
  </tr>
</table>

> Note that the flags are each powers of 2, so - with the exception of DAT - they may be toggled independently or in combination.

## Handshake Procedure

The handshake is a three-step process, with each step being repeated by its respective sender until successful.  This requires a [timeout](#Timeout) mechanism to manage retransmissions on failure (and a chance to get comfortable with this type of design before Project 07).

### Connecting Side

<ol>
<li>Send a packet with the SYN bit set to 1</li>
<li>Await a response containing the SYN and ACK bits set to 1</li>
  <ul><li>If more than 20 ms passes without a response, retransmit SYN</li></ul>
<li>Store and associate the address of the responding host with the socket (you will need to define your own map)</li>
<li>Send a packet with the ACK bits set to 1</li>
</ol>

### Accepting Side

<ol>
<li>Await a packet containing a SYN bit set to 1</li>
  <ul>
    <li>If a packet arrives that does not have the SYN bit set, discard</li>
  </ul>
<li>Store and associate the address of the sending host with the socket (you will need to define your own map)</li>
<li>Send a packet with the SYN and ACK bits set to 1</li>
  <ul>
    <li>If more than 20 ms passes without a response, retransmit the SYNACK</li>
  </ul>
</ol>

## Timeout

Enabling a timeout in a socket can be done in a few ways.  We recommend setting the <code>SO_RECVTIMEO</code> using the <code>setsockopt</code> function.  See the following code fragment for guidance:

```
#include <sys/time.h>
```
```
  struct timeval timeout = {
    .tv_usec = 20000               // 20 milliseconds --> microseconds
  };
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
```

This will cause any call to `recv` or `recvfrom` to return with an error after 20 ms if no packet is received.