/* TCPClient class
*
*	TCPClient is as the name suggests a class representing a TCPClient. The
* TCPClient only has Connect() and ResolveHost() methods. The Connect() method
* returns a pointer to a TCPSocket that can then be used to transmit data
*
* Author: Logan Anteau
*/

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "TCPSocket.h"

class TCPClient
{

public:
	TCPSocket* Connect(const char* hostname, int port);

private:
	//Resolve hostname to an ip address
	int ResolveHost(const char* hostname, struct in_addr* addr); 

};

#endif /* TCPCLIENT_H */