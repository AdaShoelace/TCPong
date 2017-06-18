#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/BroadcastServer.h"
#include "../include/Server.h"

enum{PRE_GAME, PLAYING, DECIDING};

class Controller
{
    public:
        Controller();
        ~Controller();
        void run();
        void receivedBroadcast(const sf::IpAddress& sender);
        void preGame();
        void playing();
        void deciding();
        std::vector<int> checkPollEvent();  //holds the eventloop 

    private:
        int preOrPlaying;
        std::string senderAddress;
        void initGame();
        BroadcastServer bServer;
        Server server;

        const int PADDLE_STEP = 80;

        sf::RenderWindow window; 
        
        sf::RectangleShape rightPaddle;
        sf::RectangleShape leftPaddle;

        sf::Vector2f rightPaddlePos;
        sf::Vector2f leftPaddlePos;
};

#endif //CONTROLLER_H
