# Project 3: SMTP Agent

An SMTP client that reads an email address and a text-file path, then sends that file as an email body. The exchange uses `HELO`, `MAIL FROM`, `RCPT TO`, `DATA`, the message terminator, and `QUIT`, with the same address used for sender and recipient.

## Contents

- `src/smtp_agent.c`: the SMTP command exchange and file transmission.
- `tests/p3_tests.c`: course tests for command order, message formatting, and responses.
- [requirements.md](requirements.md): the original project requirements.

## Current State

The source passes a syntax check with the shared SANS header. It reads server replies but does not validate the expected status codes or handle file-open failures. The saved implementation also ends after sending `QUIT` without reading the final server reply.

The project uses [shared support](../shared/README.md). Its course tests depend on globals from the earlier project tests and are not standalone programs.
