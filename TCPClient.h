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