#include "TCPSocket.h"
#include "TCPClient.h"
#include "Message.h"
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
		return(1);
	}

	int receivedLen;
	std::string receivedData;
	unsigned char buffer[256];
	memset(&buffer, 0, sizeof(buffer));

	TCPClient* client = new TCPClient();
	TCPSocket* socket = client->Connect(argv[1], atoi(argv[2]));

	bool received = false;
	char ack = 6; //ACK character is ASCII 6
	int numPackets = 0;

	if(socket)
	{
		while(!received)
		{
			receivedLen = socket->Receive(reinterpret_cast<char*>(buffer), sizeof(buffer));
			if(receivedLen > 0)
			{
				if(receivedLen > 2) //This is a block
				{
					std::string* block = new std::string(reinterpret_cast<const char*>(buffer));
					Message newMessage(buffer, sizeof(buffer));

					if(newMessage.isValid()) 
					{
						socket->Send(&ack, sizeof(ack));
						numPackets++;
					}
					receivedData.append(newMessage.GetDataString());
				}
				if(buffer[0] == 4) //EOT
				{
					received = true;
					socket->Close();
				}
			}
		}

		std::cout << "Received message was:" << std::endl << std::endl << receivedData << std::endl << std::endl;
		std::cout << "Number of packets received: " << numPackets << std::endl;

		delete socket;
		delete client;
		return(0);
	}
	delete socket;
	delete client;
	return(1);
}