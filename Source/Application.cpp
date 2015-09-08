#include <Application.hpp>
#include <InitialParametrs.hpp>
#include <Utility.hpp>
#include <SceneNode.hpp>
#include <Point.hpp>

#include <SFML/Window/Event.hpp>

namespace Editor
{
    Application::Application()
    : mWindow(sf::VideoMode(windowWidth, windowHeight), windowName)
    , mElements{}
    {
        init();
    }

    void Application::init()
    {
        std::unique_ptr<SceneNode> aPoint{ new Point(50.f, 50.f) };
        std::unique_ptr<SceneNode> bPoint{ new Point(50.f, 100.f) };
        std::unique_ptr<SceneNode> cPoint{ new Point(100.f, 50.f) };
        std::unique_ptr<SceneNode> dPoint{ new Point(100.f, 100.f) };

        mElements.push_back(std::move(aPoint));
        mElements.push_back(std::move(bPoint));
        mElements.push_back(std::move(cPoint));
        mElements.push_back(std::move(dPoint));

    }

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

        for (std::unique_ptr<SceneNode>& element : mElements)
        {
            mWindow.draw(*element);
        }
        mWindow.display();
    }

    void Application::update(sf::Time dt)
    {
        for (std::unique_ptr<SceneNode>& element : mElements)
        {
            element->update(dt);
        }
    }


    void Application::processEvents()
    {
        sf::Event event;

        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }
    }
}



























