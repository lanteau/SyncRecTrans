/* TCPSocket class
*
*	A TCPSocket is the bread and butter of sending data back and forth over a 
* network socket. The TCPSocket object contains a file descriptor to the
* actual socket and it's peer port and IP. The TCPSocket Send() and Receive()
* methods are used to transmit data.
*
* Author: Logan Anteau
*/

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <string>
#include <arpa/inet.h>

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

	void Close();


private:
	TCPSocket(int sockfd, struct sockaddr_in* address);
	TCPSocket();
	TCPSocket(const TCPSocket& socket);


};

#endif /* TCPSOCKET_H */