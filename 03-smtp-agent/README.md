# Project 3: SMTP Agent

This project examines a stateful application protocol by sending an email through an SMTP command exchange. The agent reads an email address and a text-file path, connects to the server, receives its greeting, and sends the commands for the sender, recipient, and message body. The same address is used in the sender and recipient fields, following the course assignment. The project shows how the next action in a protocol depends on the messages exchanged earlier in the connection.

## Main Steps

- Connect to the SMTP server and receive its initial greeting.
- Send `HELO`, `MAIL FROM`, and `RCPT TO`, receiving replies between commands.
- Send `DATA` and read the text file into the outgoing message stream.
- End the message body with the SMTP termination sequence and print the server's response.
- Send `QUIT` and disconnect from the server.

## Files

- [p3-smtp_agent.c](p3-smtp_agent.c): the SMTP commands, server replies, and file-body transmission.
- [p3-http_client.c](p3-http_client.c): the HTTP client version grouped with Assignment 3, retained under its numbered filename.
- [p3_tests.c](p3_tests.c): course tests for command order, address formatting, message termination, and response handling.
- [assignment.md](assignment.md): the detailed SMTP requirements and example exchange.
