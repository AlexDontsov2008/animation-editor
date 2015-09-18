#include <InputWindow.hpp>
#include <InitialParametrs.hpp>
#include <Utility.hpp>

#include <SFML/Window/Event.hpp>

#include <string>
#include <iostream>
#include <fstream>

namespace Editor
{
    static const sf::ContextSettings settings(24, 8, 16, 3, 0);

    InputWindow::InputWindow(InputWindow::WindowType type, const sf::RenderWindow& mainWindow,
                             const std::string& windowName, const std::string& fieldName)
    : mType(type)
    , mWindow(sf::VideoMode(400.f, 200.f), windowName, sf::Style::Close, settings)
    , mFontStorage(pathToFont)
    , mInputField(sf::Vector2f(300.f, 30.f))
    , mFieldName(fieldName, mFontStorage.getFont(), 30.f)
    , mFileNameText("", mFontStorage.getFont(), 25.f)
    , mFileNameStr("")
    , mButtons()
    , mNameLenghtLimit(15)
    {
        mWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x + mainWindow.getSize().x / 2.f - 200.f,
                                         mainWindow.getPosition().y + mainWindow.getSize().y / 2.f - 100.f));

        init();

    }

    // Helper Init function.
    void InputWindow::init()
    {
        mInputField.setFillColor(boxColor);
        mInputField.setPosition(sf::Vector2f(50.f, 60.f));
        mInputField.setOutlineThickness(2.f);
        mInputField.setOutlineColor(ActiveColor);

        mFieldName.setColor(sf::Color::White);
        mFileNameText.setColor(sf::Color::White);
        mFieldName.setPosition(40.f, 15.f);
        mFileNameText.setPosition(52.f, 58.f);

        constexpr float offsetX { 50.f }, offsetY { 130.f };
        std::unique_ptr<Button> newButtonOK { new Button(InputWindow::OkType, mFontStorage.getFont(), "OK", offsetX, offsetY, false) };
        std::unique_ptr<Button> newButtonCancel { new Button(InputWindow::CancelType, mFontStorage.getFont(), "Cancel", offsetX + 250.f, offsetY, false) };


        newButtonOK->setLabelPosition(sf::Vector2f(newButtonOK->getLabelPosition().x + 4.f,
                                                   newButtonOK->getLabelPosition().y));
        newButtonCancel->setLabelPosition(sf::Vector2f(newButtonCancel->getLabelPosition().x - 4.f,
                                                       newButtonCancel->getLabelPosition().y));
        mButtons.push_back(std::move(newButtonOK));
        mButtons.push_back(std::move(newButtonCancel));
    }

    // Run Window.
    void InputWindow::run()
    {
        sf::Clock clock;
        sf::Time elapsedTime = sf::Time::Zero;
        while(mWindow.isOpen())
        {

            elapsedTime += clock.restart();

            while (elapsedTime > dt)
            {
                elapsedTime -= dt;
                processEvents(dt);
                update(dt);
            }
            draw();
        }
    }

    // Get File Name.
    const std::string& InputWindow::getFileName() const
    {
        return mFileNameStr;
    }

    // Update window.
    void InputWindow::update(sf::Time dt)
    {
        updateInputString(dt);

        for (auto& button : mButtons)
            button->update(dt);
    }

    // Draw window.
    void InputWindow::draw()
    {
        mWindow.clear(windowColor);

        mWindow.draw(mInputField);
        mWindow.draw(mFieldName);
        mWindow.draw(mFileNameText);
        for (auto& button : mButtons)
            mWindow.draw(*button);

        mWindow.display();
    }


    // Process All Events.
    void InputWindow::processEvents(sf::Time dt)
    {
        sf::Event event;
        checkActiveElements();

        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
            }
            else if ((event.type == sf::Event::TextEntered))
            {
                if (event.text.unicode >= 32 && event.text.unicode < 127)
                {
                    if (mFileNameStr.size() < mNameLenghtLimit)
                    {
                        mFileNameStr += static_cast<char>(event.text.unicode);
                    }
                    checkStringForCursor();
                    mFileNameText.setString(mFileNameStr);
                }

            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::BackSpace))
            {
                deleteCharacter(mFileNameStr);
                mFileNameText.setString(mFileNameStr);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == static_cast<unsigned int>(sf::Mouse::Left))
            {
                processButtons();
            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                mWindow.close();
            }
        }
    }

    // Process Buttons.
    void InputWindow::processButtons()
    {
        for (auto& button : mButtons)
        {
            if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), button->getRect(), false))
            {
                if (button->getAction() == OkType)
                     processOkButton();

                else if (button->getAction() == CancelType)
                {
                    mFileNameStr = "";
                    mWindow.close();
                }
            }
        }
    }

    // Check Active Elements.
    void InputWindow::checkActiveElements()
    {
        for (auto& button : mButtons)
        {
            if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), button->getRect(), false))
                button->setActive(true);

            else
                button->setActive(false);
        }
    }

    // Update string.
    void InputWindow::updateInputString(sf::Time dt)
    {
        static float refreshTime{};
        refreshTime += dt.asSeconds();

        if (refreshTime >= 0.5f)
        {
            checkStringForCursor();

            refreshTime = 0.f;
            mFileNameText.setString(mFileNameStr);
        }
    }

    // Process Cursor.
    void InputWindow::checkStringForCursor()
    {
        if (mFileNameStr.find('|') != std::string::npos)
            mFileNameStr.erase(mFileNameStr.find('|'), 1);

        else
            mFileNameStr += '|';
    }

    // Process OK Button.
    void InputWindow::processOkButton()
    {
        if (mFileNameStr.find('|') != std::string::npos)
            mFileNameStr.erase(mFileNameStr.find('|'), 1);

        if (mType == LoadWindow)
        {
            if (mFileNameStr.find(".ani") == std::string::npos)
                mFileNameStr += ".ani";
            std::ifstream loadFile(mFileNameStr, std::ios_base::in);
            if ( loadFile.is_open())
                mWindow.close();
        }
        else if (mType == SaveWindow)
        {
            if (mFileNameStr.size() > 1)
            {
                if (mFileNameStr.find(".ani") == std::string::npos)
                    mFileNameStr += ".ani";
                mWindow.close();
            }
        }
    }



}
