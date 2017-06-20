#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <thread>

class Controller;

class Server
{
    public:
        Server(Controller& controller);
        ~Server();
        
    private:
        void listen();
        sf::TcpListener listener;
        Controller& controller;
        int listeningState;
        std::thread t2;

};

#endif //SERVER_H
