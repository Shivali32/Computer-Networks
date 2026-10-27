# Project 1: HTTP Client

A command-line client that reads an HTTP method and file path, connects to a host, sends an HTTP/1.1 request, and prints the response. This project focuses on request formatting and receiving data through the SANS helper interface.

## Contents

- `src/http_client.c`: the version saved in `Home/http_client.c`.
- `variants/http_client_alternative.c`: the alternate version saved as `A-http_client.c`.
- `variants/http_client_setup.c`: another implemented version found in the original `.setup` directory.
- `tests/p1_tests.c`: course tests for request headers and SANS calls.
- [requirements.md](requirements.md): the original project description and expectations.

## Current State

The main saved version has an unsized local `method` array and does not compile as written. The alternate versions are retained separately; they should not be linked together because they define the same function. The setup version passes a syntax check, but its receive loop stops after the total exceeds 1,024 bytes, so complete downloads are not guaranteed.

The SANS declarations and helper library are in [shared support](../shared/README.md). This folder preserves the saved implementations without changing their behavior.
