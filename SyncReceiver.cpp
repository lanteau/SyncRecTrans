#include "TCPSocket.h"
#include "TCPClient.h"
#include "Message.h"
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("usage: %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	int length;
	std::string receivedData;
	unsigned char buffer[256];
	memset(&buffer, 0, sizeof(buffer));

	TCPClient* client = new TCPClient();
	TCPSocket* socket = client->Connect(argv[1], atoi(argv[2]));

	bool received = false;
	char ack = 6;
	int numPackets = 0;

	if(socket)
	{
		while(!received)
		{
			length = socket->Receive(reinterpret_cast<char*>(buffer), sizeof(buffer));
			if(length > 0)
			{
				if(length > 2) //This is a block
				{

					std::string* block = new std::string(reinterpret_cast<const char*>(buffer));
					Message newMessage(buffer, sizeof(buffer));
					numPackets++;


					if(newMessage.isValid()) 
						socket->Send(&ack, sizeof(ack));

					receivedData.append(newMessage.GetDataString());
				}
				if(buffer[0] == 4) //EOT
				{
					received = true;
					socket->Close();
				}


			}
		}

		printf("%s%s%s", "\nReceived message was: ", receivedData.c_str(), "\n");
		printf("%s%d%s", "\nNumber of packets received: ", numPackets, "\n");

		
		delete socket;
		exit(0);
	}

	exit(1);
}