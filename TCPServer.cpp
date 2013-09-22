#include "TCPSocket.h"
#include "TCPServer.h"
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <cerrno>

TCPServer::TCPServer(int port, const char* address) :
	m_listenSD(0),
	m_portNum(port),
	m_address(address),
	m_listening(false)
{
}

TCPServer::~TCPServer()
{
	if(m_listenSD > 0)
		close(m_listenSD);
}

int TCPServer::Start()
{
	if(m_listening)
	{
		return 0;
	}

	m_listenSD = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(m_portNum);
	
	if(m_address.size() > 0)
	{
		inet_pton(AF_INET, m_address.c_str(), &(address.sin_addr));
	}
	else
		address.sin_addr.s_addr = INADDR_ANY;	//If inet_pton fails, listen on ALL network interfaces

	int optVal = 1;
	// Allows us to immediately reuse a port
	setsockopt(m_listenSD, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)); 

	int result = bind(m_listenSD, (struct sockaddr*)&address, sizeof(address));
	if(result != 0)
	{
		std::cerr << "Failed to bind to socket: " << strerror(errno) << std::endl;
		return result;
	}

	result = listen(m_listenSD, 5);
	if(result != 0)
	{
		std::cerr << "Listening failed: " << strerror(errno) << std::endl;
		return result;
	}

	m_listening = true;
	return result;

}

TCPSocket* TCPServer::Accept()
{
	if(!m_listening)
		return NULL;

	struct sockaddr_in address;
	socklen_t len = sizeof(address);
	memset(&address, 0, sizeof(address));

	int sockD = accept(m_listenSD, (struct sockaddr*)&address, &len);
	if(sockD < 0)
	{
		std::cerr << "Accept failed: " << strerror(errno) << std::endl;
		return NULL;
	}

	//Set timeout parameters
	struct timeval tv;
	tv.tv_sec = 0; // 100ms timeout
	tv.tv_usec = 1e05;
	setsockopt(sockD, SOL_SOCKET, SO_RCVTIMEO, (struct timeval*)&tv, sizeof(struct timeval));

	return new TCPSocket(sockD, &address);
}