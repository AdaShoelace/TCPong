#include "../include/BroadcastServer.h"

BroadcastServer::BroadcastServer()
: t1(&BroadcastServer::listenForBroadcast, this)
{
    listener.bind(BROADCAST_PORT);
    sf::IpAddress address;
    broadcastAddress = address.Broadcast;
}

void BroadcastServer::sendBroadcast()
{
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
        else
        {
            std::string str(data);
            std::cout << str << std::endl;
        }

    }
}
