# Project 2: HTTP Server

A small HTTP server that accepts one connection, reads the requested path, opens the file, and returns an HTTP/1.1 response. It sends the response headers first, followed by file contents in chunks of up to 1,024 bytes.

## Contents

- `src/http_server.c`: request parsing, file reading, response headers, and file transfer.
- `tests/p2_tests.c`: course tests for SANS calls, headers, and file contents.
- [requirements.md](requirements.md): the original assignment requirements.

## Current State

The source passes a syntax check with the shared SANS header. It assumes the requested file opens successfully and does not implement a missing-file response or path validation. It is a course exercise intended for local use.

This project relies on [shared support](../shared/README.md). Its tests also use globals defined in the Project 1 test file, so the test file is not a standalone executable.
