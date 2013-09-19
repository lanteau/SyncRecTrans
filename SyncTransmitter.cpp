#include "TCPSocket.h"
#include "TCPServer.h"
#include "Message.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	if(argc < 2 || argc > 4)
	{
		printf("Usage: SyncServer <port> [<ip>]\n");
		exit(1);
	}

	TCPSocket* socket = NULL;
	TCPServer* server = NULL;

	Message myMessage("Testing123");
	std::vector<std::string> blocks = myMessage.GetBlocks();

	if(argc == 3)
		server = new TCPServer(atoi(argv[1]), argv[2]);
	else
		server = new TCPServer(atoi(argv[1]));

	printf("About to start!\n");
	if(server->Start() == 0)
	{
		while(1)
		{
			printf("Accepting connections on port %s \n", argv[1]);
			socket = server->Accept();
			if(socket != NULL)
			{
				int i = 0;
				int resends = 0;		
				while(i < blocks.size() && resends < 100)
				{
					std::string block = blocks.at(i);
					for(int j = 0; j < block.length(); j++)
					{
						unsigned char test = block.at(j);
						printf("%d \n", test);
					}
					char* buffer = new char[block.length() + 1];
					char receiveBuffer[256];
					strcpy(buffer, block.c_str());
					//buffer = block.c_str();
					printf("%d", socket->Send(buffer, block.size()));
					
					printf("%s", "Waiting for ACK\n");
					int len = socket->Receive(receiveBuffer, sizeof(receiveBuffer));
					receiveBuffer[len] = NULL; //Null terminate string
					if(receiveBuffer[0] == 6) //ACK character
					{
						i++;
						receiveBuffer[0] = NULL;
					}
					else			// Need to resend block
						resends++;

					//if(resends > 100)
					//	exit(-2);
				}
				char endOfTrans = 4;
				socket->Send(&endOfTrans, sizeof(endOfTrans));
				printf("%s%d%s", "Number of resends: ", resends, "\n");
				socket->Close(); //Close connection to client


			}
		}
	}
	perror("Could not start Transmit server");
	exit(-1);
}
