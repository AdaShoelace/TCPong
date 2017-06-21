#include "../include/Server.h"
#include "../include/Controller.h"
#include <iostream>

Server::Server(Controller& controller)
    : controller(controller),
    listeningThread(&Server::listen, this),
    talkThread(&Server::talk, this)
{
    listeningState = PRE_GAME;
}

Server::~Server()
{

}

void Server::listen()
{
    bool listening = true;
    if(listener.listen(53000) != sf::Socket::Done)
    {
        listening = false;
        std::clog << "listening failed :(" << std::endl;
    }

    sf::Packet packet;
    while(listening)
    {
        if(listeningState == PRE_GAME)
        {
            if(listener.accept(session) == sf::TcpListener::Done)
            {
                listeningState = PLAYING;
                sf::Packet to_send;
                std::string asd = "Okej!";
                to_send << asd;
                session.send(to_send);
            }
        }
    }
}

void Server::talk()
{
    sf::Packet packet;
    while(true)
    {
        if(listeningState == PLAYING)
        {
            sf::TcpSocket::Status status = session.receive(packet);
            switch(status)
            {
                case sf::TcpSocket::Done:
                    {
                        std::string message;
                        packet << message;
                        if(message == "Okej!")
                        {
                            std::clog << "Received okay!" << std::endl;
                        }
                        break;
                    }

                case sf::TcpSocket::Disconnected: case sf::TcpSocket::Error:
                    listeningState = PRE_GAME;
                    controller.failedConnection();
                    std::clog << "Shit went south!" << std::endl;
                    break;

                case sf::TcpSocket::NotReady:
                    std::clog << "Not ready..." << std::endl;
                    break;
                default:
                    std::clog << "Default switch case in Server.cpp" << std::endl;
            }
        }
    }
}

void Server::accept(std::string ipAddress)
{
    session.setBlocking(false);
    session.connect(ipAddress, 53000);
    session.setBlocking(true);
    listeningState = PLAYING;
    std::clog << "Trying to connect to: " << ipAddress << std::endl;
}
