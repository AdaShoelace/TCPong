#include "../include/Server.h"
#include "../include/Controller.h"

Server::Server(Controller& controller)
    : controller(controller), t2(&Server::listen, this)
{
    listeningState = PRE_GAME; 
}

void Server::listen()
{
    while(true)
    {
        if(listeningState == PRE_GAME)
        {
             
        }
    }
}
