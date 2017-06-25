CC = g++
CFLAGS = -std=c++11 -Wall -pthread

Pong: Controller.o 
	$(CC) $(CFLAGS) -o Pong main.cpp  Controller.o BroadcastServer.o Server.o -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network

Controller.o: BroadcastServer.o Server.o
	$(CC) $(CFLAGS) -o Controller.o -c Controller.cpp -lsfml-window -lsfml-graphics

BroadcastServer.o: Server.o
	$(CC) $(CFLAGS) -o BroadcastServer.o -c BroadcastServer.cpp -lsfml-network -lsfml-system

Server.o:
	$(CC) $(CFLAGS) -o Server.o -c Server.cpp -lsfml-network

clean:
	rm Pong *.o
