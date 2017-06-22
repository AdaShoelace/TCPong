#include "../include/BroadcastServer.h"
#include "../include/Controller.h"
#include <SFML/System.hpp>

BroadcastServer::BroadcastServer(Controller& controller)
: controller(controller), myAddress(myAddress.getLocalAddress()), t1(&BroadcastServer::listenForBroadcast, this)
{
    listener.bind(BROADCAST_PORT);
    broadcastAddress = myAddress.Broadcast;
}

BroadcastServer::~BroadcastServer()
{

}

void BroadcastServer::sendBroadcast()
{
    std::cout << "Sending broadcast!" << std::endl;
    sf::Packet BroadcastPacket;
    std::string hello = "Hello world";
    BroadcastPacket << hello;
    listener.send(BroadcastPacket, broadcastAddress, BROADCAST_PORT);
}

void BroadcastServer::listenForBroadcast()
{
    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port = BROADCAST_PORT;
    while (1)
    {
        if(listener.receive(packet, sender, port)
            != sf::Socket::Done)
        {
            std::cerr << "Broadcast reception failed!" << std::endl;
        }
        else if(sender.toInteger() != myAddress.toInteger())
        {
            std::cout << "sender: " << sender << ", my address: " << myAddress << std::endl;
            controller.receivedBroadcast(sender);
        }
    }
}
