#include <Application.hpp>
#include <InitialParametrs.hpp>
#include <Utility.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include <iostream>
#include <array>
#include <stdexcept>

namespace Editor
{

    static const sf::ContextSettings settings(24, 8, 16, 3, 0);

    Application::Application()
    : mWindow(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default, settings)
    , mFontStorage { pathToFont }
    , mWorkFlow{ mWindow }
    , mButtons {}
    , mInput{ mWindow }
    , mFrameNumber{ 1 }
    {
        initButtons();
    }

    void Application::initButtons()
    {
        std::unique_ptr<Button> newButtonMove { new Button(UserInput::MoveType, mFontStorage.getFont(), "Move", 12.f, 30.f, true) };
        std::unique_ptr<Button> newButtonPoint{ new Button(UserInput::PointType, mFontStorage.getFont(), "Point", 12.f, 100.f, false) };
        std::unique_ptr<Button> newButtonLine { new Button(UserInput::LineType, mFontStorage.getFont(), "Line", 12.f, 170.f, false) };

        mButtons.push_back(std::move(newButtonMove));
        mButtons.push_back(std::move(newButtonPoint));
        mButtons.push_back(std::move(newButtonLine));
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
        mWindow.clear(windowColor);

        mWorkFlow.draw();
        for (auto& button : mButtons)
            mWindow.draw(*button);

        mWindow.display();
    }

    void Application::update(sf::Time dt)
    {
        mWorkFlow.update(dt);

        for (auto& button : mButtons)
            button->update(dt);
    }


    void Application::processEvents()
    {
        mInput.processEvents(mWorkFlow, mButtons);
    }
}



























