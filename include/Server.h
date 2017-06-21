#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <thread>
#include <string>

class Controller;

class Server
{
    public:
        Server(Controller& controller);
        ~Server();
        void accept(std::string ipAddress);
        
    private:
        void listen();
        sf::TcpListener listener;
        Controller& controller;
        int listeningState;
        std::thread listeningThread;
        sf::TcpSocket session;
};

#endif //SERVER_H
