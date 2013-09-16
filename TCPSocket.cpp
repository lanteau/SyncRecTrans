#include "TCPSocket.h"

TCPSocket::TCPSocket(int sockfd, struct sockaddr_in* address)
: m_sockfd(sockfd)
{
  char ip[50];
  inet_ntop(PF_INET, (struct in_addr*) &(address->sin_addr.s_addr), ip, sizeof(ip)-1);
  m_peerIP = ip;
  m_peerPort = ntohs(address->sin_port);

}

TCPSocket::~TCPSocket()
{
  close(m_sockfd);
}

ssize_t TCPSocket::Send(char* buffer, size_t len)
{
  return write(m_sockfd, buffer, len);
}

ssize_t TCPSocket::Receive(char* buffer, size_t len)
{
  return read(m_sockfd, buffer, len);
}

std::string TCPSocket::GetPeerIP()
{
  return m_peerIP;
}

int TCPSocket::GetPeerPort()
{
  return m_peerPort;
}