all: SyncTransmitter SyncReceiver

SyncTransmitter:
SyncTransmitter : SyncTransmitter.o SyncTransmitter.cpp TCPSocket.o TCPServer.o Message.o
	g++ -o SyncTransmitter SyncTransmitter.o TCPSocket.o TCPServer.o Message.o FileReader.o

SyncTransmitter.o : SyncTransmitter.cpp TCPSocket.o TCPServer.o Message.o TCPClient.o FileReader.o
	g++ -c SyncTransmitter.cpp

TCPSocket.o : TCPSocket.h TCPSocket.cpp
	g++ -c TCPSocket.cpp

TCPServer.o : TCPSocket.o TCPServer.h TCPServer.cpp
	g++ -c TCPServer.cpp

TCPClient.o : TCPSocket.o TCPClient.h TCPClient.cpp
	g++ -c TCPClient.cpp
	
Message.o : Message.h Message.cpp
	g++ -c Message.cpp

FileReader.o : FileReader.h FileReader.cpp
	g++ -c FileReader.cpp

SyncReciever:
SyncReceiver : SyncReceiver.o
	g++ -o SyncReceiver SyncReceiver.o TCPSocket.o TCPClient.o Message.o

SyncReceiver.o : SyncReceiver.cpp TCPSocket.o TCPClient.o Message.o
	g++ -c SyncReceiver.cpp


clean:
	rm -f *.o SyncTransmitter SyncReceiver
