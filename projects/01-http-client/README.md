# Project 1: HTTP Client

This project explores HTTP from the client's side by constructing an HTTP/1.1 request and reading a server's response. The client takes a method and a path from standard input, connects to a host and port, and sends the request through the SANS networking interface. It then receives response data in a loop, prints the bytes to the terminal, and closes the connection. The assignment separates the HTTP message format from the underlying socket implementation so that the request line, headers, and response handling can be studied directly.

## Main Steps

- Read the HTTP method and path, with the path supplied without a leading slash.
- Construct the request line and headers, including the host and port, user agent, cache control, and connection preference.
- Send the request using `sans_send_pkt` and read the response using `sans_recv_pkt`.
- Print the response and track the received byte count before disconnecting.

## Files

- [p1-http_client.c](p1-http_client.c): the HTTP client and its request and response handling.
- [p1_tests.c](p1_tests.c): course tests that examine request headers, arguments passed to SANS functions, and response handling.
- [assignment.md](assignment.md): the complete assignment description, including header requirements and examples.

The client uses the declarations in the [SANS interface header](../../miscellaneous/shimate-main/src/include/sans.h). The course [helper-library notes](../../miscellaneous/Course.wiki/archive.md) describe the connect, send, receive, and disconnect functions.
