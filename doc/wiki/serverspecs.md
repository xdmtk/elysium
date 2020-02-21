### General 

The server at the moment essentially acts as a repeater among connected clients. On execution, the server binds and listens to a specified port and waits for incoming client connections. 

For each new client connection, a new thread is spawned on the server, which manages a send/receive loop for messages between the client and server. 

When a message is received from the client, the server takes the message and sends it out to all connected clients. 


### Proposed Features
* Authentication (Serverside)
* Private Messaging Support
* Message Protocol
