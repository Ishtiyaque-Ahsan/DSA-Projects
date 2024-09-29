Here, Implemented Socket Programming in C++ using Go-Back-N Approach.

This program in supported in Ubuntu/Linux OS only.

we have 2 files here , one for sender and other for receiver node.

For localhost :

open 2 terminals in your Ubuntu for each programs :

First Run Receiver Program then execute Sender Program.

Here a sequence of integer numbers is passed from sender to receiver as the representation of a packet.

Note : Here an integer number represents a packet.

Once receiver receives a packet/number, it sends acknowledment to sender.

Following Go-Back_N Approach of Packet Transfer, all methods are implemented.

Here is brief about Go-Back-N:

The Go-Back-N (GBN) approach in socket programming is a sliding window protocol used for 
reliable data transmission. It allows the sender to transmit multiple frames before needing 
an acknowledgment, but the receiver only accepts in-sequence frames. 
If a frame is lost or corrupted, all subsequent frames are discarded, and the sender must retransmit
the lost frame and all following ones. 
This approach ensures reliability but can be inefficient due to redundant retransmissions.
GBN is commonly used in TCP for flow control and error handling.
