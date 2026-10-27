# Project 1 - HTTP Client

> In this project, we will be starting our exploration of the HTTP protocol by writing a simple HTTP client.  This client will allow us to download
> files over HTTP on the command line just like the back end of your favorite browser.  For this first project, we'll be providing all of the
> networking components behind a few library calls (see [Appendix](#Appendix)).  Instead, this project will focus on the HTTP protocol itself
>  
> Our task will be to send the correct request string to the server, then download and parse the response.

# Tasks

Below is a bullet point list of the individual requirements and expectations for this project.  Every project will contain a list of expectations that you must fulfill to get full credit for the assignment.  Each assignment will include a _Setup_ section with any required build steps, followed by a _Requirements_ section that will list what conditions we will be evaluating.  Finally, we will include any restrictions or prohibitions for each project at the end of this section.

#### Setup
  - [ ] Install scons in user mode
```
pip install --user scons
```
  - [ ] Add the following line to your `~/.bashrc` file if necessary 
```
PATH=$PATH:~/.local/bin
```
  - [ ] Checkout the source files for the project (where `#` is replaced by the project number) from the root directory of your repository
```bash
scons checkout project=#
```

#### Requirements
  - [ ] Submission MUST implement the `http_client` function in the _src/http_client.c_ file
    - [ ] Function MUST prompt the user for two values
      - [ ] The first value MUST be read as the `method` of the request (for this project, only GET is required)
      - [ ] The second value MUST be read as the `path` of the request
        - [ ] `path` MUST NOT include the leading `/` character when read from the user
    - [ ] Function MUST connect to the provided `host` and `port` using the provided `sans_connect` (See [Appendix](#Appendix))
    - [ ] All packets MUST be 1024 bytes or less (maximum buffer size)
    - [ ] Function MUST send a valid HTTP request using the `sans_send_pkt` (see [Appendix](#Appendix))
      - [ ] Request MUST be HTTP version 1.1
      - [ ] Request MUST include a `Host` header
        - [ ] `Host` MUST match the string `host:port` where host and port match the arguments to `sans_connect`
      - [ ] Request MUST include a `User-Agent` header
        - [ ] User-Agent SHOULD be `sans/1.0`
      - [ ] Request MUST include a `Cache-Control` header
        - [ ] Cache-Control MUST be `no-cache`
      - [ ] Request MUST include a `Connection` header
        - [ ] Connection MUST be `close`
      - [ ] Request MUST include an `Accept` header
        - [ ] Accept SHOULD be `*/*`
    - [ ] Function MUST receive response from the server using the provided `sans_recv_pkt` (See [Appendix](#Appendix))
      - [ ] Function MUST receive entire page including headers
      - [ ] (BONUS <sub>strongly recommended</sub>) Function SHOULD scan response headers for the `Content-Length` header
        - [ ] Function SHOULD use the `Content-Length` header to determine how many calls to `sans_recv_pkt` are made beyond the response headers
      - [ ] Calls to `sans_recv_pkt` MUST NOT exceed 1024 buffer size
      - [ ] Function MUST print the headers and data as it is received from the server
    - [ ] Function MUST disconnect from the socket using the provided `sans_disconnect` (See [Appendix](#Appendix))
 
### Restrictions

For this project, you may only use the following library functions:

  - `strncmp` or `strcmp`
  - `strlen`
  - `strtol`
  - `printf` or `fprintf`
  - `snprintf` (strongly recommended)
  - `scanf`
  - Any function listed in [Appendix A](#Appendix)
  - Any function written by you

#### <i>Note</i>
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

#### <b>A. <a href="archive">Helper Library</a></b>
#### <b>B. <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview#requests">HTTP Protocol</a></b>