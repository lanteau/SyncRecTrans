all: SyncTransmitter SyncReceiver

SyncTransmitter:
SyncTransmitter : SyncTransmitter.o SyncTransmitter.cpp TCPSocket.o TCPServer.o Message.o
	g++ -ggdb -o SyncTransmitter SyncTransmitter.o TCPSocket.o TCPServer.o Message.o

SyncTransmitter.o : SyncTransmitter.cpp TCPSocket.o TCPServer.o Message.o TCPClient.o
	g++ -ggdb -c SyncTransmitter.cpp

TCPSocket.o : TCPSocket.h TCPSocket.cpp
	g++ -ggdb -c TCPSocket.cpp

TCPServer.o : TCPSocket.o TCPServer.h TCPServer.cpp
	g++ -ggdb -c TCPServer.cpp

TCPClient.o : TCPSocket.o TCPClient.h TCPClient.cpp
	g++ -ggdb -c TCPClient.cpp
	
Message.o : Message.h Message.cpp
	g++ -ggdb -c Message.cpp

SyncReciever:
SyncReceiver : SyncReceiver.o
	g++ -ggdb -o SyncReceiver SyncReceiver.o TCPSocket.o TCPClient.o Message.o

SyncReceiver.o : SyncReceiver.cpp TCPSocket.o TCPClient.o Message.o
	g++ -ggdb -c SyncReceiver.cpp


clean:
	rm -f *.o SyncServer
