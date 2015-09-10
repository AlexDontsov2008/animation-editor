#include <Application.hpp>
#include <InitialParametrs.hpp>
#include <Utility.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include <iostream>
#include <array>

namespace Editor
{
    Application::Application()
    : mWindow(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default)
    , mWorkFlow{ mWindow }
    {}

    void Application::run()
    {
        sf::Clock clock;
        sf::Time elapsedTime = sf::Time::Zero;

        while (mWindow.isOpen())
        {
            elapsedTime += clock.restart();

            while (elapsedTime > dt)
            {
                elapsedTime -= dt;
                processEvents();
                update(dt);
            }
            render();
        }
    }

    void Application::render()
    {
        mWindow.clear(sf::Color::White);

        mWorkFlow.draw();

        mWindow.display();
    }

    void Application::update(sf::Time dt)
    {
        mWorkFlow.update(dt);
    }


    void Application::processEvents()
    {
        sf::Event event;

        static unsigned short numPoint { 0 };
        constexpr static float offset { 10.f };
        constexpr static short maxPoints{ 2 };
        static std::array<sf::Vector2f, maxPoints> linePositions;

        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == static_cast<uint32_t>(sf::Mouse::Left))
            {
                sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);
                sf::FloatRect positionRect = mWorkFlow.getRect();


                if ((positionRect.left + offset < positionMouse.x && positionMouse.x < positionRect.left + positionRect.width - offset) &&
                    (positionRect.top + offset < positionMouse.y && positionMouse.y < positionRect.top + positionRect.height - offset))
                {
                    //mWorkFlow.addPoint(sf::Vector2f(positionMouse.x, positionMouse.y));
                    numPoint += 1;
                    linePositions[(numPoint - 1) % maxPoints] = sf::Vector2f(positionMouse.x, positionMouse.y);

                    if (numPoint == 2)
                    {
                        numPoint = 0;
                        mWorkFlow.addLine(linePositions[0], linePositions[1]);
                    }
                }

            }
        }
    }
}



























