#include <UserInput.hpp>
#include <Utility.hpp>
#include <InitialParametrs.hpp>
#include <Point.hpp>

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
        SceneNode* activeElement = checkActiveElements(workFlow, buttons);
        //checkActiveElements(workFlow, buttons);
        processMouseMoveInstrument(workFlow, sf::Mouse::getPosition(mWindow), activeElement);

        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                    mWindow.close();
            if (event.type == sf::Event::MouseButtonPressed && event.key.code == static_cast<unsigned int>(sf::Mouse::Left))
            {
                if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), workFlow.getRect(), true))
                    processInstruments(workFlow, activeElement);
                else
                    processButtons(buttons, event);
            }
        }
    }


    // Function for process every Instrument!!!!
    void UserInput::processMouseMoveInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement)
    {
        if (activeElement != nullptr && activeElement->getNodeType() == SceneNode::Point)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Point* point = static_cast<Point*>(activeElement);
                point->setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
            }
        }
    }

    void UserInput::processPointInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement)
    {
        if (activeElement == nullptr)
            workFlow.addPoint(sf::Vector2f(mousePosition.x, mousePosition.y));
        else
            std::cout << "In this coords, we already have an object\n";
    }

    void UserInput::processLineInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement)
    {
        static unsigned short numPoint { 0 };
        constexpr static short maxPoints{ 2 };

        static std::array<Point*, maxPoints> points{};

        if (activeElement != nullptr && activeElement->getNodeType() == SceneNode::Point)
        {
            numPoint += 1;
            points[(numPoint - 1) % maxPoints] = static_cast<Point*>(activeElement);
            points[(numPoint - 1) % maxPoints]->setEnable(true);
        }

        if (numPoint == maxPoints)
        {
            numPoint = 0;
            points[0]->setEnable(false);
            points[1]->setEnable(false);
            if (points[0] != points[1])
                workFlow.addLine(points[0]->getPosition(), points[1]->getPosition());
        }

    }

    void UserInput::processInstruments(WorkFlow& workFlow, SceneNode* activeElement)
    {
        sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);

        switch (mType)
        {
            case MoveType:
                //processMouseMoveInstrument(workFlow, positionMouse, activeElement);
                break;

            case PointType:
                processPointInstrument(workFlow, positionMouse, activeElement);
                break;

            case LineType:
                processLineInstrument(workFlow, positionMouse, activeElement);
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
                for (auto& enableButton : buttons)
                {
                    if (enableButton->getEnable() && enableButton == button)
                        return;
                    else
                        enableButton->setEnable(false);
                }
                button->setEnable(true);
                setInstrumentType(static_cast<InstrumentType>(button->getAction()));
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

    SceneNode* UserInput::checkActiveElements(WorkFlow& workFlow, std::vector<std::unique_ptr<Button>>& buttons) const
    {
        if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), workFlow.getRect(), true))
        {
            workFlow.setActive(true);
            return checkActiveDrawingElements(workFlow);
        }
        else
        {
            workFlow.setActive(false);
            for (auto& button : buttons)
            {
                if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), button->getRect(), false))
                    button->setActive(true);
                else
                    button->setActive(false);
            }
        }
        return nullptr;
    }

    // Check active draw elements (Points, Lines).
    SceneNode* UserInput::checkActiveDrawingElements(WorkFlow& workFlow) const
    {
        for (auto& element : workFlow.setElements())
        {
            if (isActiveDrawingElement(sf::Mouse::getPosition(mWindow), element->getRect(), element.get()))
            {
                element->setActive(true);
                return element.get();
            }
            else
                element->setActive(false);
        }
        return nullptr;
    }
}
