#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>

class Server
{
    public:
        Server();
        ~Server();
    private:
        sf::TcpListener listener;
};

#endif //SERVER_H
