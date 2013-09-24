#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>

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

	//Blocking. Returns pointer to TCPSocket of connected client
	TCPSocket* Accept(); 
	
private:
	TCPServer() {}

};

#endif /* TCPSERVER_H */