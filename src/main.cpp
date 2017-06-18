#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/BroadcastServer.h"


int main()
{

    const int PADDLE_STEP = 80;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
    window.setVerticalSyncEnabled(true);
    sf::Event event;

    sf::Vector2u screenSize = window.getSize();
    const int SCREEN_WIDTH = screenSize.x;
    std::cout << SCREEN_WIDTH << " width " << std::endl;
    const int SCREEN_HEIGHT = screenSize.y;
    std::cout << SCREEN_HEIGHT << " height " << std::endl;

    sf::RectangleShape leftPaddle(sf::Vector2f(30, 100));
    sf::Vector2f leftPaddlePos((float)leftPaddle.getSize().x,(float)SCREEN_HEIGHT / 2 - leftPaddle.getSize().y / 2);


    sf::RectangleShape rightPaddle(sf::Vector2f(30, 100));
    sf::Vector2f rightPaddlePos((float)SCREEN_WIDTH - rightPaddle.getSize().x * 2, (float)SCREEN_HEIGHT / 2 - leftPaddle.getSize().y / 2);

    std::cout << leftPaddlePos.x << " " << leftPaddlePos.y << std::endl;

    sf::Clock clock;
    sf::Time deltaTime;

    BroadcastServer broadcastServer;

    while(window.isOpen())
    {
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

    return 0;
}
