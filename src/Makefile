Pong: Controller.o 
	g++ -std=c++11 -Wall -pthread -o Pong main.cpp  Controller.o -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network

Controller: BroadcastServer.o Server.o
	g++ -std=c++11 -Wall -pthread -c Controller.cpp -lsfml-window -lsfml-graphics

BroadcastServer:
	g++ -std=c++11 -Wall -pthread -c BroadcastServer.cpp -lsfml-network

Server:
	g++ -std=c++11 -Wall -pthread -c Server.cpp -lsfml-network

clean:
	rm -rf Pong
