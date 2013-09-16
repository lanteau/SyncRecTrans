SyncTransmitter : SyncTransmitter.o SyncTransmitter.cpp TCPSocket.o TCPServer.o Message.o
	g++ -ggdb -o SyncTransmitter SyncTransmitter.o TCPSocket.o TCPServer.o Message.o

SyncTransmitter.o : SyncTransmitter.cpp TCPSocket.o TCPServer.o Message.o
	g++ -ggdb -c SyncTransmitter.cpp

TCPSocket.o : TCPSocket.h TCPSocket.cpp
	g++ -ggdb -c TCPSocket.cpp

TCPServer.o : TCPSocket.o TCPServer.h TCPServer.cpp
	g++ -ggdb -c TCPServer.cpp
	
Message.o : Message.h Message.cpp
	g++ -ggdb -c Message.cpp

clean:
	rm -f *.o SyncServer
