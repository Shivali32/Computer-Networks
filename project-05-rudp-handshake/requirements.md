> Original assignment text from the Indiana University Computer Networks course wiki, Fall 2024. The commands below describe the original course environment and its single `src/` directory. See [this project's README](README.md) and [shared support](../shared/README.md) for the files available in this reorganized repository.

# Project 5 - Reliable UDP and the RUDP Handshake

> In this project, we will begin moving from TCP to our custom protocol - Reliable UDP.  This protocol will use UDP packets at layer 4 to carry our
> data, but we will be implementing TCP-like features by injecting our own headers into the payloads and providing connection-oriented behavior with
> reliability guarantees.
> 
> For this project, we will just be switching our socket functions to use UDP rather than TCP and implementing a simple handshake to take the place
> of the connect and accept functions.

# Tasks

Below is a bullet point list of the individual requirements and expectations for this project.  Every project will contain a list of expectations that you must fulfill to get full credit for the assignment.  Each assignment will include a _Setup_ section with any required build steps, followed by a _Requirements_ section that will list what conditions we will be evaluating.  Finally, we will include any restrictions or prohibitions for each project at the end of this section.

#### Setup
  - [ ] Checkout the source files for the project (where `#` is replaced by the project number) from the root directory of your repository
```bash
scons checkout project=#
```

#### Requirements
  - [ ] Submission MUST reimplement the `sans_connection`, `sans_accept` and `sans_disconnection` functions in the _src/sans_socket.c_ file
  - [ ] Submission MUST implement the `sans_recv_pkt` and `sans_send_pkt` functions in the _src/sans_transport.c_ file
  - [ ] Submission MUST NOT disrupt the behavior of `http_client`, `http_server` and `smtp_agent`
    - [ ] All tests for these functions SHOULD behave exactly the same after substituting your new implementation

##### _sans_connect_
  - [ ] Function MUST check the `protocol` value
    - [ ] If `protocol` is `IPPROTO_TCP` function MUST behave as before
    - [ ] If `protocol` is `IPPROTO_RUDP` function MUST implement the new behavior below
  - [ ] Function MUST create a SOCK_DGRAM socket using an IPPROTO_UDP protocol
  - [ ] Function MUST NOT call the `connect` function
  - [ ] Function MUST perform a 3-way handshake with the remote server (See [Appendix A](#Appendix))
    - [ ] Handshake MUST use the `sendto` and `recvfrom` functions
  - [ ] Function MUST create a record of the connection that stores the address of the server

##### _sans_accept_
  - [ ] Function MUST check the `protocol` value
    - [ ] If `protocol` is `IPPROTO_TCP` function MUST behave as before
    - [ ] If `protocol` is `IPPROTO_RUDP` function MUST implement the new behavior below
  - [ ] Function MUST create a SOCK_DGRAM socket with an IPPROTO_UDP interface
  - [ ] Function MUST NOT call the `listen` or `accept` functions
  - [ ] Function MUST preform a 3-way handshake with the remote client (See [Appendix A](#Appendix))
    - [ ] Handshake MUST use the `recvfrom` and `sendto` functions
  - [ ] Function MUST create a record of the connection that stores the address of the connecting client

##### _sans_send_pkt_
  - [ ] Function MUST call `sendto` to transmit the buffer

##### _sans_recv_pkt_
  - [ ] Function MUST call `recvfrom` to receive to the buffer

### Restrictions
For this project, you may only use the following library functions:

  - `socket`
  - `sendto` and `recvfrom`
  - Any function written by you

#### <i>Note</i>
> Functions in this list are ONLY those that are required to implement NEW code for this project.  Any function already in your file is still fair game.

> Not all of these functions are necessary for all implementations of this project

## Building and Testing

You may build the project using `scons` with the following command

```
scons build
```

<details>
<summary><i>Details</i></summary>

----

This will produce two executables: `sans` and `sans-tests`.  The former will run your code as expected and as shown in the examples below.  The
latter will run a suite of tests as defined in the `p1_tests.c` file provided for this project.  Run `sans` with no arguments to see help test 
with explanations for how to execute each project.  In the case of `http_client` for instance, you would run the following:

```
./sans http client www.example.com 80
```

You can debug the program or tests using `gdb` with the `--args` flag.  Let's say you are testing the `http_client` implementation, you could run gdb for testing like so:

```
gdb --args ./sans http client www.example.com 80
```
> Note that everything following the `--args` flag is exactly the same as running your program like normal.

This command may also be used on the test scripts to get a better idea of what is being examined during testing.

</details>

## Examples

<details>
<summary>HTTP Client</summary>

##### Command
```
./sans http client www.example.com 80
```

##### Input
```
GET index.html
```

##### Output
```
HTTP/1.1 200 OK
Accept-Ranges: bytes
Age: 305420
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Mon, 19 Aug 2024 07:14:08 GMT
Etag: "3147526947+gzip"
Expires: Mon, 26 Aug 2024 07:14:08 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Server: ECAcc (chd/07A8)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1256
Connection: close

<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;

    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>
```

</details>

## Appendices

#### <b>A. <a href="../shared/rudp-handshake.md">RUDP 3-Way Handshake</a></b>
#### <b>B. <a href="https://man7.org/linux/man-pages/man3/sendto.3p.html">sendto Manual Page</a></b>
#### <b>C. <a href="https://man7.org/linux/man-pages/man3/recvfrom.3p.html">recvfrom Manual Page</a></b>
