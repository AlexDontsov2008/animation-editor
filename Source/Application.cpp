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
    : mWindow(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Close, settings)
    , mFontStorage { pathToFont }
    , mWorkFlows{}
    , mButtons {}
    , mFramesCounterText{}
    , mInput{ mWindow }
    , mFrameNumber{ 0 }
    {
        std::unique_ptr<WorkFlow> newWorkFlow { new WorkFlow(mWindow) };
        mWorkFlows.push_back(std::move(newWorkFlow));
        constexpr float offsetY { 65.f };
        mFramesCounterText.setFont(mFontStorage.getFont());
        mFramesCounterText.setString("Frame: " + toString(mFrameNumber + 1) + " / " + toString(mWorkFlows.size()));
        mFramesCounterText.setCharacterSize(20);
        mFramesCounterText.setColor(sf::Color::White);
        mFramesCounterText.setStyle(sf::Text::Bold);
        mFramesCounterText.setPosition(workAreaPosX, mWindow.getSize().y - offsetY);
        initButtons();
    }

    void Application::initButtons()
    {
        constexpr float offsetX { 28.f };
        constexpr float offsetY { 70.f };
        std::unique_ptr<Button> newButtonSelect { new Button(UserInput::SelectType, mFontStorage.getFont(), "Select", offsetX, 30.f, true) };
        std::unique_ptr<Button> newButtonMove { new Button(UserInput::MoveType, mFontStorage.getFont(), "Move", offsetX, 30.f + offsetY, false) };
        std::unique_ptr<Button> newButtonPoint{ new Button(UserInput::PointType, mFontStorage.getFont(), "Point", offsetX, 30.f + 2.f * offsetY, false) };
        std::unique_ptr<Button> newButtonLine { new Button(UserInput::LineType, mFontStorage.getFont(), "Line", offsetX, 30.f + 3.f * offsetY, false) };
        std::unique_ptr<Button> newButtonAddFrame { new Button(UserInput::AddFrameType, mFontStorage.getFont(), "  Add.  \nFrame", offsetX, 30.f + 4.f * offsetY, false) };
        std::unique_ptr<Button> newButtonDeleteFrame { new Button(UserInput::DeleteFrameType, mFontStorage.getFont(), "  Del.  \nFrame", offsetX, 30.f + 5.f * offsetY, false) };
        std::unique_ptr<Button> newButtonLoad { new Button(UserInput::LoadType, mFontStorage.getFont(), "Load", offsetX, 30.f + 6.f * offsetY, false) };
        std::unique_ptr<Button> newButtonSave { new Button(UserInput::SaveType, mFontStorage.getFont(), "Save", offsetX, 30.f + 7.f * offsetY, false) };
        std::unique_ptr<Button> newButtonExit { new Button(UserInput::ExitType, mFontStorage.getFont(), "Exit", offsetX, 30.f + 8.f * offsetY, false) };

        constexpr float offset { 2.f };

        newButtonSelect->setLabelPosition(sf::Vector2f(newButtonSelect->getLabelPosition().x - offset * 2.f,
                                                       newButtonSelect->getLabelPosition().y));
        newButtonPoint->setLabelPosition(sf::Vector2f(newButtonPoint->getLabelPosition().x - offset,
                                                      newButtonPoint->getLabelPosition().y));
        newButtonAddFrame->setLabelPosition(sf::Vector2f(newButtonAddFrame->getLabelPosition().x - offset,
                                                         newButtonAddFrame->getLabelPosition().y - offset * 5.f));
        newButtonDeleteFrame->setLabelPosition(sf::Vector2f(newButtonDeleteFrame->getLabelPosition().x - offset,
                                                            newButtonDeleteFrame->getLabelPosition().y - offset * 5.f));
        newButtonExit->setLabelPosition(sf::Vector2f(newButtonExit->getLabelPosition().x + offset,
                                                      newButtonExit->getLabelPosition().y));

        mButtons.push_back(std::move(newButtonSelect));
        mButtons.push_back(std::move(newButtonMove));
        mButtons.push_back(std::move(newButtonPoint));
        mButtons.push_back(std::move(newButtonLine));
        mButtons.push_back(std::move(newButtonAddFrame));
        mButtons.push_back(std::move(newButtonDeleteFrame));
        mButtons.push_back(std::move(newButtonLoad));
        mButtons.push_back(std::move(newButtonSave));
        mButtons.push_back(std::move(newButtonExit));
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

        mWindow.draw(mFramesCounterText);
        mWorkFlows[mFrameNumber]->draw();

        for (auto& button : mButtons)
            mWindow.draw(*button);

        mWindow.display();
    }

    void Application::update(sf::Time dt)
    {
        mWorkFlows[mFrameNumber]->update(dt);
        mFramesCounterText.setString("Frame: " + toString(mFrameNumber + 1) + " / " + toString(mWorkFlows.size()));

        for (auto& button : mButtons)
            button->update(dt);
    }


    void Application::processEvents()
    {
        mInput.processEvents(mWorkFlows, mButtons, mFrameNumber);
    }
}



























