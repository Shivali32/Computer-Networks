Original assignment description from the [Fall 2024 course wiki](../../miscellaneous/Course.wiki/project-3.md). Paths and SCons commands in this description refer to the course build layout.

# Project 3 - SMTP Agent

> In this project we will be exploring the idea of a persistent, stateful protocol by implementing an SMTP agent.  This agent will connect to another
> SMTP agent and send an email using the SMTP protocol.  Once we have completed the implementation of the SMTP agent, we will be able to send a file
> as an email to a valid address.
>  
> For security reasons, we have modified the remote SMTP agent used in this project to only accept emails where both the TO and FROM fields are set to
> your personal email address.  By default, SMTP has no meaningful mechanisms to prevent misuse and spamming - these exist in most email applications, 
> but the protocol itself is very permissive.  This restriction ensures that we do not unintentionally spam unrelated email addresses.  So keep this
> restriction in mind while you are creating your implementation.

# Tasks

Below is a bullet point list of the individual requirements and expectations for this project.  Every project will contain a list of expectations that you must fulfill to get full credit for the assignment.  Each assignment will include a _Setup_ section with any required build steps, followed by a _Requirements_ section that will list what conditions we will be evaluating.  Finally, we will include any restrictions or prohibitions for each project at the end of this section.

#### Setup
  - [ ] Checkout the source files for the project (where `#` is replaced by the project number) from the root directory of your repository
```bash
scons checkout project=#
```

#### Requirements
  - [ ] Submission MUST implement the `smtp_agent` function in the _src/smtp_agent.c_ file
    - [ ] Function MUST take two strings from standard in
      - [ ] The first string MUST be used as the sender and receiver 
      - [ ] The second string MUST be used as the path to a file
        - [ ] This file MAY include any plain text body
    - [ ] Function MUST connect to the remote agent using the `sans_connection` function
    - [ ] Function MUST follow the SMTP exchange protocol
      - [ ] Function MUST send each message using the `sans_send_pkt` function
      - [ ] Function MUST receive the response after each message using the `sans_recv_pkt` function
      - [ ] Function MUST send a HELO message
        - [ ] Function MUST ensure the response begins with "250"
      - [ ] Function MUST send a MAIL FROM message
      - [ ] Function MUST send a RCPT TO message
      - [ ] Function MUST send a DATA message
      - [ ] Function MUST send the contents of the email file
        - [ ] Email file MAY be any length
        - [ ] Agent MUST add a termination condition if email file does not contain one
      - [ ] Function MUST send DATA termination string
        - [ ] Function MUST print the response from the termination string
        - [ ] Response SHOULD contain a valid token as a Base64 sequence of characters (see [Examples](#Exampples))
      - [ ] Function MUST send QUIT message
    - [ ] Function MUST disconnect from the connection

### Restrictions

For this project, you may only use the following library functions:

  - `strncmp` or `strcmp`
  - `printf` or `fprintf`
  - `snprintf`
  - `scanf` or `sscanf`
  - `stat`
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
<summary>SMTP Agent</summary>

##### Command
```
./sans smtp client lunar.open.sice.indiana.edu 25
```

##### Input
> In this example, we use a fake example email and presume an `email.txt` file in the current directory containing an email body.
```
example@iu.edu
email.txt
```

##### Output
> The example code used to generate this output printed the response for every request.  For full credit, the only line required is the final 
> 250 response containing the gibberish character sequence (the grading token).
```
220 lunar SMTP - Mail proxy and grading portal
250 lunar
250 OK
250 OK
354 End data with <CR><LF>.<CR><LF>
250 b'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJob3N0bmFtZSI6ImplbXVzc2VyQGl1LmVkdSIsInNlbmRlciI6ImplbXVzc2VyQGl1LmVkdSIsInJlY2lldmVycyI6WyJqZW11c3NlckBpdS5lZHUiXSwiYm9keSI6IiNxY24gJW4-dG5cciIsInR0bCI6MH0.kK-uplY1nzt24wYxk0i5dGYxjh_VH8QO1gO7ULkWRnM'
221 Bye
```

</details>

## Appendices

#### <b>A. <a href="../../miscellaneous/Course.wiki/archive.md">Helper Library</a></b>
#### <b>B. <a href="https://en.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol">SMTP Protocol</a></b>
