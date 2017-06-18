#include "../include/BroadcastServer.h"

BroadcastServer::BroadcastServer()
: t1(&BroadcastServer::listenForBroadcast, this)
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
    BroadcastPacket<<"Hello world";
    listener.send(BroadcastPacket, broadcastAddress, BROADCAST_PORT);
}

void BroadcastServer::listenForBroadcast()
{
    char data[100];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port = BROADCAST_PORT;
    while (1)
    {
        if(listener.receive(data, 100, received, sender, port)
        != sf::Socket::Done)
        {
            std::cerr << "Broadcast reception failed!" << std::endl;
        }
        else if(sender.toInteger() != myAddress.getLocalAddress().toInteger())
        {
            std::string str(data);
            std::cout << "sender: " << sender << std::endl;
            std::cout << "my address: " << myAddress << std::endl;
            std::cout << str << std::endl;
        }
        else
        {
          std::cout << "Some douchebag is spamming my port. It might be myself:" << std::endl;
          std::cout << sender << std::endl;
        }

    }
}
