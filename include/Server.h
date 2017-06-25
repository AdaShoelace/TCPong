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
        void send(std::string json);

    private:
        void listen();
        void talk();
        sf::TcpListener listener;
        Controller& controller;
        int listeningState;
        std::thread listeningThread;
        std::thread talkThread;
        sf::TcpSocket session;
};

#endif //SERVER_H
