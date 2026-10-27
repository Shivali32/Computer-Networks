# Project 7 - Driver and Go-Back-N

> In this project, we will be improving our implementation for Stop-and-Wait by implementing a "backend" worker thread and increasing the
> queue size for Stop-and-Wait, transforming it into Go-Back-N.  This model reflects the way your Operating System actually handles packets
> when calling `sans_send_pkt` (or <samp>send</samp> in the actual TCP implementation), where the send function only passes the packet to
> a backend worker which is constantly listening for work to perform.  The send function then immediately returns, allowing the backend
> worker to handle the packet.

This project will have two parts: implementing the `sans_backend` function to actual perform the work on the sent packet and implementing the Go-Back-N algorithm inside `sans_backend` to handle a queue of packets.  We have provided the threading code in an updated version of <samp>sans.c</samp> file, which will run the `sans_backend` function (found in the <samp>sans_backend.c</samp> file) as a second thread.

# Tasks

Below is a bullet point list of the individual requirements and expectations for this project.  Every project will contain a list of expectations that you must fulfill to get full credit for the assignment.  Each assignment will include a _Setup_ section with any required build steps, followed by a _Requirements_ section that will list what conditions we will be evaluating.  Finally, we will include any restrictions or prohibitions for each project at the end of this section.

#### Setup
  - [ ] Download the updated <samp>sans.c</samp> and <samp>sans_backend.c</samp> files and place them in your `src/` directory
  - [ ] Checkout the source files for the project (where `#` is replaced by the project number) from the root directory of your repository
```bash
scons checkout project=#
```

#### Requirements
  - [ ] Submission MUST reimplement the `sans_send_pkt` and `sans_recv_pkt` functions in the _src/sans_transport.c_ file
  - [ ] Submission MUST NOT disrupt the behavior of `http_client`, `http_server` and `smtp_agent`
    - [ ] All tests for these functions SHOULD behave exactly the same after substituting your new implementation
      - (Note) These modes will no longer work against websites such as Google or Facebook, but will work against each other

##### _sans_send_pkt_
  - [ ] Function MUST NOT perform any work on the data/payload except as described below
  - [ ] Function MUST build a `rudp_packet_t` out of the provided data
  - [ ] Function MUST enqueue the packet to the `send_window` (See <samp>sans_backend.c</samp>)

##### _sans_backend_
  - [ ] Function MUST perform the following forever
    - [ ] Function MUST send all pending, unsent packets in the `send_window`
    - [ ] Function MUST attempt to receive an acknowledgement from the remote host
      - [ ] If acknowledgement times out, function MUST re-send all packets in the `send_window`
      - [ ] If acknowledgement is correct, function MUST remove the acknowledged packet from the `send_window`
    - [ ] `send_window` SHOULD be structured as a <a href="https://en.wikipedia.org/wiki/Circular_buffer">ring buffer</a>.

##### _sans_recv_pkt_ (Should require minimal/no change from previous project)
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