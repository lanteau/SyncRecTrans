#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include <netinet/in.h>
#include "TCPSocket.h"
#include <string.h>

class TCPServer
{
	int m_listenSD;
	std::string m_address;
	int m_portNum;
	bool m_listening;

public:
	TCPServer(int port, const char* address="");
	~TCPServer();

	int Start();
	TCPSocket* Accept();

private:
	TCPServer() {}

};


#endif /* TCPSERVER_H */