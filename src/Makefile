Pong: BroadcastServer.o
	g++ -std=c++11 -o Pong main.cpp BroadcastServer.o -lsfml-window -lsfml-system -lsfml-graphics

BroadcastServer.o:
	g++ -std=c++11 -c BroadcastServer.cpp -lpthread

clean:
	rm -rf pong
