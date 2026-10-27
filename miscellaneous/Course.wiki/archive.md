# Helper Functions for SANS

We provide you with a library of functions contained in the `src/testing/templates.a` file.  Since we will be starting at the top of the network stack - the Application Layer - these functions will serve as temporary scaffolding to support your code until we are ready to implement their behaviors ourselves.  By the end of the semester, you will have written ALL of the features provided by these functions and replaced them with your own implementations.

----

### _sans_connect_ 
<table>
<tr><th></th><th>Type</th><th>Description</th></tr>
<tr>
  <td rowspan="3">Arguments</td>
  <td width="15%">const char*</td>
  <td>This argument takes a string with the hostname or IP address to connect to.  (i.e. <code>"www.google.com"</code> or <code>"192.168.1.1"</code>)</td></tr>
<tr>
  <td>int</td>
  <td>This argument takes an integer port used to connect to a remote server.</td>
</tr>
<tr>
  <td>int</td>
  <td>This argument takes an integer and indicates the transport protocol used by the connection.  For projects 1 and 2, this MUST be the macro <code>IPPROTO_TCP</code> (defined in &lt;netinet/in.h&gt;), for projects 5 and greater, this should be the macro <code>IPPROTO_RUDP</code> (defined in "include/rudp.h")</td>
</tr>
<tr>
  <td>Returns</td>
  <td>int</td>
  <td>Returns a "socket" identifier.  Consider this just as an ID that is passed to other functions to indicate that they operate on this connection.</td></tr>
<tr>
  <td>About</td>
  <td colspan="2">This function establishes a persistent connection to a server described by the <code>host</code> and <code>port</code> pair.</td>
</tr>
</table>

### _sans_accept_
<table>
<tr><th></th><th>Type</th><th>Description</th></tr>
<tr>
  <td rowspan="3">Arguments</td>
  <td width="15%">const char*</td>
  <td>This argument takes a string containing the IP address or hostname at which a connection should listen for an incoming connection</td></tr>
<tr>
  <td>int</td>
  <td>This argument takes an integer port that the server should listen for incoming connections</td>
</tr>
<tr>
  <td>int</td>
  <td>This argument indicates the transport protocol used by the connection.  For projects 1 and 2, this MUST be the macro <code>IPPROTO_TCP</code> (defined in &lt;netinet/in.h&gt;), for projects 5 and greater, this should be the macro <code>IPPROTO_RUDP</code> (defined in "include/rudp.h")</td>
</tr>
<tr>
  <td>Returns</td>
  <td>int</td>
  <td>Returns a "socket" identifier.  Consider this just as an ID that is passed to other functions to indicate that they operate on this connection.</td></tr>
<tr>
  <td>About</td>
  <td colspan="2">This function blocks, waiting until a corresponding connection is made from a remote host, then returns a socket referencing the connection.  This function is almost always called on a server to await connections from a client.</td>
</tr>
</table>

### _sans_send_pkt_ 
<table>
<tr><th></th><th>Type</th><th>Description</th></tr>
<tr>
  <td rowspan="3">Arguments</td>
  <td width="15%">int</td>
  <td>This argument takes an integer socket ID.  This ID indicates which connection the buffer transmit over.</td></tr>
<tr>
  <td>const char*</td>
  <td>This argument takes a buffer containing data to be sent to a remote host.</td>
</tr>
<tr>
  <td>int</td>
  <td>This argument takes an integer containing the length of the buffer to be transmitted.</td>
</tr>
<tr>
  <td>Returns</td>
  <td>int</td>
  <td>Returns an integer length indicating how many bytes were successfully transmitted to the remote host.</td></tr>
<tr>
  <td>About</td>
  <td colspan="2">This function takes a buffer to transmit over a connection - represented by a socket ID - and sends that data to an awaiting, corresponding <code>sans_recv_pkt</code> function</td>
</tr>
</table>

### _sans_recv_pkt_
<table>
<tr><th></th><th>Type</th><th>Description</th></tr>
<tr>
  <td rowspan="3">Arguments</td>
  <td width="15%">int</td>
  <td>This argument takes an integer socket ID.  This ID indicates which connection the buffer transmit over.</td></tr>
<tr>
  <td>char*</td>
  <td>This argument takes a buffer that will be written to with the data received.</td>
</tr>
<tr>
  <td>int</td>
  <td>This argument takes an integer length indicating the maximum size of the buffer.  The function will never write more than this many bytes to the buffer.</td>
</tr>
<tr>
  <td>Returns</td>
  <td>int</td>
  <td>Returns an integer number of bytes written to the buffer.  This returns 0 if no bytes were written or -1 if there is a failure.</td></tr>
<tr>
  <td>About</td>
  <td colspan="2">This function blocks and awaits a packet to be received by a corresponding <code>sans_send_pkt</code> call.  This data is copied into the buffer passed into the function.</td>
</tr>
</table>

### _sans_disconnect_
<table>
<tr><th></th><th>Type</th><th>Description</th></tr>
<tr>
  <td rowspan="1">Arguments</td>
  <td width="15%">int</td>
  <td>This argument takes an integer socket ID.  This ID indicates which connection to disconnect.</td>
</tr>
<tr>
  <td>Returns</td>
  <td>int</td>
  <td>Returns an integer 0 on success or -1 on failure.</td></tr>
<tr>
  <td>About</td>
  <td colspan="2">This function closes and releases the resources used by this connection.</td>
</tr>
</table>