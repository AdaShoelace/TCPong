#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BroadcastServer.h"
#include "Server.h"
#include "json.hpp"

enum{PRE_GAME, PLAYING, DECIDING};

class Controller
{
    public:
        Controller();
        ~Controller();
        void run();
        void receivedBroadcast(const sf::IpAddress& sender);
        void preGame();
        void playing(sf::Time time);
        void deciding();
        void checkPollEvent();  //holds the eventloop 
        void failedConnection();
        void successfullyConnected(bool isLeft);
        void receivedData(nlohmann::json j);

    private:
        int preOrPlaying;
        bool isLeft;
        sf::Font font;
        std::string senderAddress;
        void initGame();
        Server server;
        BroadcastServer bServer;

        const int PADDLE_STEP;

        sf::RenderWindow window; 
        
        sf::RectangleShape rightPaddle;
        sf::RectangleShape leftPaddle;

        sf::Vector2f rightPaddlePos;
        sf::Vector2f leftPaddlePos;
};

#endif //CONTROLLER_H
