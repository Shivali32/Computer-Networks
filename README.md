# Computer Networks

C networking projects from Indiana University Bloomington's Computer Networks course, Fall 2024. The work follows the network stack from HTTP and SMTP applications to sockets, reliable UDP, and packet retransmission.

Each project folder brings together its source files, available course tests, and a short README. Projects 1 through 7 also include their original assignment requirements.

## Projects

- **[Project 1: HTTP Client](project-01-http-client/)**  
  A command-line HTTP client that builds an HTTP/1.1 request and prints the server's response using the SANS networking interface.

- **[Project 2: HTTP Server](project-02-http-server/)**  
  A small HTTP server that reads a requested file and sends its contents with HTTP response headers in chunks of up to 1,024 bytes.

- **[Project 3: SMTP Agent](project-03-smtp-agent/)**  
  An email client that follows the SMTP command exchange and sends a text file as the message body.

- **[Project 4: Sockets and DNS](project-04-sockets-and-dns/)**  
  TCP connection functions built around hostname resolution, socket creation, connecting, listening, accepting, and closing connections.

- **[Project 5: RUDP Handshake](project-05-rudp-handshake/)**  
  A reliable UDP connection setup using a three-way handshake, saved peer addresses, and datagram send and receive functions.

- **[Project 6: Stop and Wait](project-06-stop-and-wait/)**  
  Packet delivery using sequence numbers, acknowledgements, and retransmission while waiting for one packet at a time.

- **[Project 7: Driver and Go-Back-N](project-07-go-back-n/)**  
  A background transport worker and ring buffer that queue multiple packets, process acknowledgements, and resend pending packets after a timeout.

- **[Project 8: Network Proxy](project-08-network-proxy/)**  
  The network proxy stage of the course. The available files contain a starter function and test placeholder; a working proxy implementation is not present.

## Shared Support

The [shared folder](shared/) holds the SANS interface, command-line driver, test utilities, helper library, and original build scripts. Earlier projects use the course helper library; later projects replace parts of it with their own socket and transport functions.

These are saved course versions, with existing implementation and build limitations described in each project README. The original SCons commands in the assignment pages refer to the former single-directory course layout, rather than eight independent applications.

## Course Context

The project names and requirements come from the [Fall 2024 course wiki](https://github.iu.edu/Luddy-Net-FA24/Course/wiki/Syllabus), which may require an IU login. Course-provided support files retain their [original license](shared/LICENSE).
