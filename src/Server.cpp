#include "../include/Server.h"
#include "../include/Controller.h"
#include <iostream>

Server::Server(Controller& controller)
    : controller(controller), listeningThread(&Server::listen, this)
{
    listeningState = PRE_GAME; 
}

Server::~Server()
{

}

void Server::listen()
{
    sf::Packet packet;
    while(true)
    {
        if(listeningState == PRE_GAME)
        {
            if(listener.accept(session) == sf::TcpListener::Done)
            {
                listeningState = PLAYING;
                sf::Packet to_send;
                to_send >> "Okej!";
                session.send(to_send);
            }
        }
        else if(listeningState == PLAYING)
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
                    std::clog << "Shit went south!" << std::endl;
                    break;

                case sf::TcpSocket::NotReady:
                    //Probably connecting at the moment
                    break;
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
