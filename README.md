# Computer Networks

This repository contains seven C programming projects from the Fall 2024 Computer Networks course at Indiana University Bloomington. The assignments work through the network stack from application protocols to connection management and reliable data transfer. The HTTP client constructs requests and reads server responses, while the HTTP server parses a request and returns a file with response headers. The SMTP agent follows a sequence of commands to send a text file as an email. The socket assignment introduces hostname resolution and TCP client and server connections using POSIX socket functions. The next assignment adds a three-way handshake over UDP and records peer addresses for packet transmission. Stop and Wait introduces sequence numbers, acknowledgements, receive timeouts, and retransmission for one packet at a time. The final assignment extends this approach with a background worker and a Go-Back-N send window, allowing several packets to be sent before their acknowledgements are processed. Together, the projects cover protocol formatting, file transfer, socket programming, connection state, and the relationship between application code and transport behavior.

## Projects

- **[Project 1: HTTP Client](01-http-client/)**  
  Build an HTTP/1.1 request from a method and path, send it through the SANS interface, and print the server's response.

- **[Project 2: HTTP Server](02-http-server/)**  
  Accept a request, read the requested file, and return its contents with HTTP response headers in chunks of up to 1,024 bytes.

- **[Project 3: SMTP Agent](03-smtp-agent/)**  
  Follow the SMTP command exchange to send a text-file message body, using one email address for the sender and recipient.

- **[Project 4: Sockets and DNS](04-sockets-and-dns/)**  
  Resolve hostnames and manage TCP connections using `getaddrinfo`, `socket`, `connect`, `bind`, `listen`, `accept`, and `close`.

- **[Project 5: RUDP Handshake](05-rudp-handshake/)**  
  Establish a connection over UDP through a three-way handshake, keep the peer's address, and send and receive datagrams.

- **[Project 6: Stop and Wait](06-stop-and-wait/)**  
  Track packet sequence numbers, wait for acknowledgements, and retransmit packets when a timeout or an incorrect acknowledgement occurs.

- **[Project 7: Driver and Go-Back-N](07-go-back-n/)**  
  Queue packets in a ring buffer and use a background worker to transmit the send window, handle acknowledgements, and retry pending packets.

## Project Files

Each project folder contains its numbered source files, course tests, assignment requirements, and a README explaining the project and its files.
