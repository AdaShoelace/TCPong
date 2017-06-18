#include "../include/Controller.h"


Controller::Controller()
{
    preOrPlaying = PRE_GAME;
}

Controller::~Controller()
{

}

void Controller::receivedBroadcast(const sf::IpAddress& sender)
{
    if(preOrPlaying == PRE_GAME)
    {
        preOrPlaying = DECIDING;
        senderAddress = sender.toString();
    }
}

void Controller::initGame()
{
    window.create(sf::VideoMode(800, 600), "Pong");
    window.setVerticalSyncEnabled(true);
    sf::Vector2u screenSize = window.getSize();
    const int SCREEN_WIDTH = screenSize.x;
    const int SCREEN_HEIGHT = screenSize.y;

    rightPaddle.setSize(sf::Vector2f(30, 120));
    leftPaddle.setSize(sf::Vector2f(30, 120));

    leftPaddlePos = sf::Vector2f((float)leftPaddle.getSize().x,(float)SCREEN_HEIGHT / 2 - leftPaddle.getSize().y / 2);
    
    rightPaddlePos = sf::Vector2f((float)SCREEN_WIDTH - rightPaddle.getSize().x * 2, (float)SCREEN_HEIGHT / 2 - leftPaddle.getSize().y / 2);
}

void Controller::run()
{

    sf::Event event;

    sf::Clock clock;
    sf::Time deltaTime;

    BroadcastServer broadcastServer;

    while(window.isOpen())
    {

        switch(preOrPlaying)
        {
            case PRE_GAME:
                preGame();
                break;

            case PLAYING:
                playing();
                break;

            case DECIDING:
                deciding();
                break;
        }

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                leftPaddlePos.y += PADDLE_STEP;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                leftPaddlePos.y -= PADDLE_STEP;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                broadcastServer.sendBroadcast();
            }
        }
        deltaTime = clock.restart();
        leftPaddle.setPosition(leftPaddlePos);
        rightPaddle.setPosition(rightPaddlePos);
        window.clear();
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.display();
    }
}

void Controller::preGame()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        preOrPlaying = PLAYING;
        //TODO send senderAddress to server
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
         
    }
}
