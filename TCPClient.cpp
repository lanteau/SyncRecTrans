#include <string>
#include "TCPClient.h"
#include <string.h>
#include <netdb.h>
#include <cstdio>

TCPSocket* TCPClient::Connect(const char* hostname, int port)
{
	struct sockaddr_in address;

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port); //Converts to network byte order

	//Attempts to resolve a hostname to an ip
	if(ResolveHost(hostname, &(address.sin_addr)) != 0)
		inet_pton(AF_INET, hostname, &(address.sin_addr)); //Converts from text to binary form

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Together AF_INET and SOCK_STREAM specify TCP/IP
	if(connect(sockfd, (struct sockaddr*)&address, sizeof(address)) != 0 )
	{
		return NULL;
	}
	return new TCPSocket(sockfd, &address);
}

int TCPClient::ResolveHost(const char* hostname, struct in_addr* addr)
{
	struct addrinfo* res;
	int result = getaddrinfo(hostname, NULL, NULL, &res);

	if(result == 0)
	{
		memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
		freeaddrinfo(res);
	}
	return result;
}