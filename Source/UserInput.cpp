#include <UserInput.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace Editor
{
    UserInput::UserInput(sf::RenderWindow& window)
    : mWindow(window)
    , mType(MoveType)
    {}


    void UserInput::processEvents(WorkFlow& workFlow, std::vector<std::unique_ptr<Button>>& buttons)
    {
        sf::Event event;
        if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), workFlow.getRect(), true))
        {
            workFlow.setBorderColor(sf::Color::White);
        }
        else
        {
            workFlow.setBorderColor(GrayColor);
            for (auto& button : buttons)
            {
                if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), button->getRect(), false))
                    button->setActive(true);
                else
                    button->setActive(false);
            }
        }

        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                    mWindow.close();
            if (event.type == sf::Event::MouseButtonPressed && event.key.code == static_cast<unsigned int>(sf::Mouse::Left))
            {
                if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), workFlow.getRect(), true))
                {
                    processInstruments(workFlow, event);
                }
                else
                {
                    processButtons(buttons, event);
                }
            }
        }
    }


    // Function for process every Instrument
    void UserInput::processMouseMoveInstrument(WorkFlow& workFlow, sf::Event event, sf::Vector2i mousePosition)
    {
        // ...
    }

    void UserInput::processPointInstrument(WorkFlow& workFlow, sf::Event event, sf::Vector2i mousePosition)
    {
        workFlow.addPoint(sf::Vector2f(mousePosition.x, mousePosition.y));
    }

    void UserInput::processLineInstrument(WorkFlow& workFlow, sf::Event event, sf::Vector2i mousePosition)
    {
        static unsigned short numPoint { 0 };
        constexpr static short maxPoints{ 2 };
        static std::array<sf::Vector2f, maxPoints> linePositions;

        workFlow.addPoint(sf::Vector2f(mousePosition.x, mousePosition.y));
        numPoint += 1;
        linePositions[(numPoint - 1) % maxPoints] = sf::Vector2f(mousePosition.x, mousePosition.y);

        if (numPoint == maxPoints)
        {
            numPoint = 0;
            workFlow.addLine(linePositions[0], linePositions[1]);
        }
    }

    // Check Mouse position. If isWorkArea == true then evalute with offset.
    bool UserInput::isMousePositionInArea(const sf::Vector2i& mousePosition, const sf::FloatRect& workArea, bool isWorkArea)
    {
        if (isWorkArea)
            return (workArea.left + workAreaOffset < mousePosition.x && mousePosition.x < workArea.left + workArea.width - workAreaOffset) &&
                   (workArea.top + workAreaOffset < mousePosition.y  && mousePosition.y < workArea.top + workArea.height - workAreaOffset);

        return (workArea.left <= mousePosition.x && mousePosition.x <= workArea.left + workArea.width) &&
               (workArea.top <= mousePosition.y  && mousePosition.y <= workArea.top + workArea.height);
    }

    void UserInput::processInstruments(WorkFlow& workFlow, sf::Event event)
    {
        sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);

        switch (mType)
        {
            case MoveType:
                processMouseMoveInstrument(workFlow, event, positionMouse);
                break;

            case PointType:
                processPointInstrument(workFlow, event, positionMouse);
                break;

            case LineType:
                processLineInstrument(workFlow, event, positionMouse);
                break;
        }
    }

    void UserInput::processButtons(std::vector<std::unique_ptr<Button>>& buttons, sf::Event event)
    {
        sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);
        for (auto& button : buttons)
        {
            if (isMousePositionInArea(positionMouse, button->getRect(), false))
            {
                button->setEnable(true);
                setInstrumentType(static_cast<InstrumentType>(button->getAction()));
            }
            else
            {
                button->setEnable(false);
            }
        }
    }


    // Get and Set methods for Instrument type.
    UserInput::InstrumentType UserInput::getInstrumentType() const
    {
        return mType;
    }

    void UserInput::setInstrumentType(InstrumentType type)
    {
        mType = type;
    }
}
