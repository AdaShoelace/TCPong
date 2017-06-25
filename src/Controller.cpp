#include "../include/Controller.h"

using namespace nlohmann;

Controller::Controller()
    : server(*this), bServer(*this),PADDLE_STEP(80)
{
    preOrPlaying = PRE_GAME;
    font.loadFromFile("Roboto-Bold.ttf");
    
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
    initGame();
    sf::Clock clock;
    sf::Time deltaTime;


    while(window.isOpen())
    {
        window.clear();

        switch(preOrPlaying)
        {
            case PRE_GAME:
                preGame();
                break;

            case PLAYING:
                playing(deltaTime);
                break;

            case DECIDING:
                deciding();
                break;
        }

        deltaTime = clock.restart();
        window.display();
    }
}

void Controller::preGame()
{
    sf::Event event;

    if(window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyReleased
            && event.key.code == sf::Keyboard::Return)
        {
            bServer.sendBroadcast(); 
        }
    }

    sf::Text text("PRE_GAME", font, 30);
    window.draw(text);
    text.setColor(sf::Color::White);
}

void Controller::playing(sf::Time time)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(isLeft)
            {
                leftPaddlePos.y -= (window.getSize().y/3) * time.asSeconds();
            }
            else
            {
                rightPaddlePos.y -= (window.getSize().y/3) * time.asSeconds();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(isLeft)
            {
                leftPaddlePos.y += (window.getSize().y/3) * time.asSeconds();
            }
            else
            {
                rightPaddlePos.y += (window.getSize().y/3) * time.asSeconds();
            }
        }
    }
    leftPaddle.setPosition(leftPaddlePos);
    rightPaddle.setPosition(rightPaddlePos);
    sf::Vector2u winSize = window.getSize();
    json gameState = {
        {"left",
            {
                {"x", leftPaddlePos.x/winSize.x},
                {"y", leftPaddlePos.y/winSize.y}
            }
        },
        {"right",
            {
                {"x", rightPaddlePos.x/winSize.x},
                {"y", rightPaddlePos.y/winSize.y}
            }
        },
        
    };
    server.send(gameState.dump());
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    sf::Text text("PLAYING", font, 30);
    text.setColor(sf::Color::White);
    window.draw(text);
}

void Controller::deciding()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) 
    {
        server.accept(senderAddress);
        preOrPlaying = PLAYING;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        preOrPlaying = PRE_GAME; 
    }
    sf::Text text("DECIDING", font, 30);
    text.setColor(sf::Color::White);
    window.draw(text);
}

void Controller::failedConnection()
{
    preOrPlaying = PRE_GAME;
}

void Controller::successfullyConnected(bool isLeft)
{
    this->isLeft = isLeft; 
    preOrPlaying = PLAYING;
}

void Controller::checkPollEvent()
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Controller::receivedData(nlohmann::json j)
{
    if(isLeft)
    {
        rightPaddlePos.x = j["right"]["x"];
        rightPaddlePos.y = j["right"]["y"];
    }
    else
    {
        leftPaddlePos.x = j["left"]["x"]; 
        leftPaddlePos.x = j["left"]["y"]; 
    }
}
