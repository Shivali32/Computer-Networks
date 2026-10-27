# Project 6 - Stop and Wait

> In this project, we will be implementing the slower of the two reliability techniques used by our RUDP protocol.  This technique - Stop and Wait - 
> sends a single packet at a time and will continue to send this packet until it receives an acknowledgement from the remote end that the packet has
> been handled.  This technique is slow, but reasonably simple to conceptualize.  We will be upgrading it to a faster approach in the next project.

# Tasks

Below is a bullet point list of the individual requirements and expectations for this project.  Every project will contain a list of expectations that you must fulfill to get full credit for the assignment.  Each assignment will include a _Setup_ section with any required build steps, followed by a _Requirements_ section that will list what conditions we will be evaluating.  Finally, we will include any restrictions or prohibitions for each project at the end of this section.

#### Setup
  - [ ] Checkout the source files for the project (where `#` is replaced by the project number) from the root directory of your repository
```bash
scons checkout project=#
```

#### Requirements
  - [ ] Submission MUST reimplement the `sans_send_pkt` and `sans_recv_pkt` functions in the _src/sans_transport.c_ file
  - [ ] Submission MUST NOT disrupt the behavior of `http_client`, `http_server` and `smtp_agent`
    - [ ] All tests for these functions SHOULD behave exactly the same after substituting your new implementation

##### _sans_connect_
  - [ ] Socket MUST be modified to allow a timeout during packet receipt

##### _sans_send_pkt_
  - [ ] Function MUST send data as a `rudp_packet_t` structure
  - [ ] Function MUST call `sendto` to transmit the buffer
  - [ ] Function MUST track a sequence number
  - [ ] Function MUST retransmit on timeout or incorrect sequence number
  - [ ] Function MUST only return once an ACK packet with the correct sequence

##### _sans_recv_pkt_
  - [ ] Function MUST receive data as a `rudp_packet_t` structure
  - [ ] Function MUST call `recvfrom` to receive to the buffer
  - [ ] Function MUST track a sequence number
  - [ ] Function MUST acknowledge the last valid packet on packet receipt

### Restrictions
There are no meaningful restrictions on this project.

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

#### <b>A. <a href="saw">Stop and Wait</a></b>