# Project 2: HTTP Server

This project covers the server side of an HTTP file exchange. The server accepts a connection, receives a request, extracts the requested file path, and reads the file from disk. It constructs an HTTP/1.1 response with the file length, content type, and connection header, then sends the file contents in chunks of up to 1,024 bytes. The project connects request parsing and file operations with the structure of an HTTP response.

## Main Steps

- Accept a client through `sans_accept` and receive the request through `sans_recv_pkt`.
- Parse the method and file path from the request line.
- Open the file, determine its length, and construct the response headers.
- Send the headers and file contents through `sans_send_pkt`.
- Release the file buffer and close the connection through `sans_disconnect`.

## Files

- [p2-http_server.c](p2-http_server.c): request parsing, file reading, response formatting, and chunked file transmission.
- [p2_tests.c](p2_tests.c): course tests for connection calls, response headers, and small and large file responses.
- [assignment.md](assignment.md): the full assignment requirements and HTTP exchange examples.

The server uses the [SANS interface](../../miscellaneous/shimate-main/src/include/sans.h). Its course tests share variables with the [Project 1 test file](../01-http-client/p1_tests.c) and use the common test utilities in the [course framework](../../miscellaneous/shimate-main/src/testing/).
