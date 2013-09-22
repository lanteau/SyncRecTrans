#include "TCPSocket.h"
#include "TCPServer.h"
#include "Message.h"
#include "FileReader.h"
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cerrno>
#include <unistd.h>


int main(int argc, char** argv)
{
	if(argc < 3 || argc > 4)
	{
		std::cout << "Usage: SyncServer <filename.txt> <port> [<ip>]" << std::endl;
		return 1;
	}

	TCPSocket* socket = NULL;
	TCPServer* server = NULL;
	FileReader myFile(argv[1]);
	try
	{
		myFile.Parse();
	}
	catch(int e)
	{
		std::cerr << "Could not parse input file: " << strerror(e) << std::endl;
		return 2;
	}

	std::vector<Message> messages = myFile.GetMessages();
	
	int portNum = atoi(argv[2]);
	if(portNum < 1025)
	{
		std::cerr << "Error: port number must be above 1024" << std::endl;
		return 3;
	} 

	if(argc == 4)
		server = new TCPServer(atoi(argv[2]), argv[3]);
	else
		server = new TCPServer(atoi(argv[2]));

	if(server->Start() == 0)
	{
		std::cout << "Listening for connections on port " << argv[2] << "..." << std::endl;

		while(1)
		{
			socket = server->Accept();
			if(socket != NULL)
			{
				int pid = fork();
  				if(pid < 0)
  				{
  					std::cerr << "Error on fork: " << strerror(errno) << std::endl;
  					return(1);
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
							receiveBuffer[0] = 0;
						}
						else // Need to resend block
							resends++;
					}
				
					char endOfTrans = 4;
					socket->Send(&endOfTrans, sizeof(endOfTrans));
					std::cout << "Number of resent blocks: " << resends << std::endl;
					socket->Close(); //Close connection to client
					return (0);
				}
				else
				{
					socket->Close();
				}


			}
		}
	}
	std::cerr << "Could not start Transmit server: " << strerror(errno) << std::endl;
	return(-1);
}
