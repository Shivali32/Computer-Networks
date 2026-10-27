> Original assignment text from the Indiana University Computer Networks course wiki, Fall 2024. The commands below describe the original course environment and its single `src/` directory. See [this project's README](README.md) and [shared support](../shared/README.md) for the files available in this reorganized repository.

# Project 2 - HTTP Server

> In this project, we will complete our examination of HTTP by implementing the server application.  Our server will have the minimal feature set to
> function as an HTTP server and act as a complement to our client.  For this project, we will only be implementing responses to GET requests and only
> one type of server error - 404 File not Found.

### WARNING

As defined in this project, our HTTP server is a MAJOR security vulnerability.  The `sans_accept` function is designed to help mitigate the danger by only accepting a single request before terminating.  While it is not an explicit requirement for grading (it is more work than is reasonable for a single week project), we strongly recommend you implement a check ("validate" and "sanitize") on the HTTP `path` to ensure it is not accessing files outside of the current directory.  We also recommend only using `localhost` (see [Example](#Examples)) for the host argument when running `./sans`.  This will ensure connections from outside silo will not be accepted.

In addition, you will not be able to run your server on port 80 for security reasons.  There is also a risk of attempting to use a port another student is currently using.  We recommend selecting a random port within the 7000-9000 range, if your program fails and prints an error from the accept call, try again with a different socket.

# Tasks

Below is a bullet point list of the individual requirements and expectations for this project.  Every project will contain a list of expectations that you must fulfill to get full credit for the assignment.  Each assignment will include a _Setup_ section with any required build steps, followed by a _Requirements_ section that will list what conditions we will be evaluating.  Finally, we will include any restrictions or prohibitions for each project at the end of this section.

#### Setup
  - [ ] Checkout the source files for the project (where `#` is replaced by the project number) from the root directory of your repository
```bash
scons checkout project=#
```

#### Requirements
  - [ ] Submission MUST implement the `http_server` function in the _src/http_server.c_ file
    - [ ] Function MUST accept a connection from a remote client using `sans_accept`
    - [ ] Function MUST receive a request from the remote client using `sans_recv_pkt`
      - [ ] Function MAY assume the request is contained in a single 1024 packet
    - [ ] Function MUST send an HTTP response using `sans_send_pkt`
      - [ ] All packets MUST be 1024 or less bytes (max buffer size)
      - [ ] Response MUST be in HTTP version 1.1
        - [ ] Response MUST contain a `Content-Length` header
          - [ ] Content-Length MUST contain the correct file length in bytes
        - [ ] Response MUST contain a `Content-Type` header
          - [ ] Content-Type MUST have value `text/html; charset=utf-8`
        - [ ] Response MUST contain the contents of the file read from disk
          - [ ] File MUST be read from the `path` value from the HTTP request
          - [ ] Response MUST include all bytes from the file, regardless of file length
    - [ ] Function MUST close the connection with `sans_disconnect` after completing response

### Restrictions

For this project, you may only use the following library functions:

  - `strncmp` or `strcmp`
  - `strlen`
  - `strtol`
  - `printf` or `fprintf`
  - `snprintf`
  - `scanf` or `sscanf`
  - `stat` (strongly recommended)
  - `fopen`, `fread`, and `fclose`
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
./sans http server localhost 8888
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
./sans http server localhost 8888
```

##### Output

You can download and print a file in the current directory with:
```
./sans http client localhost 8888
```

> Fun fact - If you download your `sans` application to a local linux host, you would be able to open your files in a web browser by navigating
> to `http://localhost:8888` (assuming the above command is run).  While our features are limited, this is fully compatible with modern web browsers.

</details>

## Appendices

#### <b>A. <a href="../shared/helper-library.md">Helper Library</a></b>
