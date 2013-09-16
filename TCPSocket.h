#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>

class TCPSocket 
{
	int m_sockfd;
	int m_peerPort;
	std::string m_peerIP;
	sockaddr_in serv_addr, cli_addr;

public:
	friend class TCPServer;
	friend class TCPClient;

	~TCPSocket();

	ssize_t Send(char* buffer, size_t len);
	ssize_t Receive(char* buffer, size_t len);

	std::string GetPeerIP();
	int GetPeerPort();


private:
	TCPSocket(int sockfd, struct sockaddr_in* address);
	TCPSocket();
	TCPSocket(const TCPSocket& socket);


};

#endif /* TCPSOCKET_H */