#include "TCPSocket.h"
#include "TCPServer.h"
#include "Message.h"
#include "FileReader.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	if(argc < 2 || argc > 4)
	{
		printf("Usage: SyncServer <filename.txt> <port> [<ip>]\n");
		exit(1);
	}

	TCPSocket* socket = NULL;
	TCPServer* server = NULL;

	FileReader myFile(argv[1]);
	std::vector<Message> messages = myFile.GetMessages();

	if(argc == 4)
		server = new TCPServer(atoi(argv[2]), argv[3]);
	else
		server = new TCPServer(atoi(argv[2]));

	if(server->Start() == 0)
	{
		while(1)
		{
			printf("Accepting connections on port %s \n", argv[2]);
			socket = server->Accept();
			if(socket != NULL)
			{
				int pid = fork();
  				if(pid < 0)
  				{
  					perror("ERROR on fork\n");
  					exit(1);
  				}
  				if(pid == 0)
  				{
  					delete server;

					int i = 0;
					int resends = 0;		
					while(i < messages.size() && resends < 100)
					{
						Message currMsg = messages.at(i);

						char buffer[256];
						char receiveBuffer[256];
						memset(&buffer, 0, sizeof(buffer)); // Clear buffer

						for(int j = 0; j < currMsg.GetFrameLength(); j++)
							buffer[j] = currMsg.GetRawString()[j];

						socket->Send(buffer, sizeof(buffer));

						int len = socket->Receive(receiveBuffer, sizeof(receiveBuffer));
						if(receiveBuffer[0] == 6) //ACK character
						{
							i++;
							receiveBuffer[0] = NULL;
						}
						else // Need to resend block
							resends++;
					}
				
					char endOfTrans = 4;
					socket->Send(&endOfTrans, sizeof(endOfTrans));
					printf("%s%d%s", "Number of resends: ", resends, "\n");
					socket->Close(); //Close connection to client
					exit(0);
				}
				else
				{
					socket->Close();
				}


			}
			perror("Error on Accept!");
		}
	}
	perror("Could not start Transmit server");
	exit(-1);
}
