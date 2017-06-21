#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include <string>

#define BROADCAST_PORT 26385

class Controller;

class BroadcastServer
{
    public:
        BroadcastServer(Controller& controller);
        ~BroadcastServer();
        void sendBroadcast();
        void listenForBroadcast();

    private:
        sf::UdpSocket listener;
        sf::IpAddress broadcastAddress;
        Controller& controller;
        sf::IpAddress myAddress;
        std::thread t1;
};

#endif //SERVER_H
