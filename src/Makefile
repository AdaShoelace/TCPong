Pong: Controller.o 
	g++ -std=c++11 -Wall -pthread -o Pong main.cpp  Controller.o BroadcastServer.o Server.o -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network

Controller: BroadcastServer.o Server.o
	g++ -std=c++11 -Wall -pthread -o Controller.o -c Controller.cpp -lsfml-window -lsfml-graphics

BroadcastServer:
	g++ -std=c++11 -Wall -pthread -o BroadcastServer.o -c BroadcastServer.cpp -lsfml-network -lsfml-system

Server:
	g++ -std=c++11 -Wall -pthread -o Server.o -c Server.cpp -lsfml-network

clean:
	rm -rf Pong *.o
