#include <UserInput.hpp>
#include <Utility.hpp>
#include <InitialParametrs.hpp>
#include <Point.hpp>
#include <Line.hpp>

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace Editor
{
    UserInput::UserInput(sf::RenderWindow& window)
    : mWindow(window)
    , mType(MoveType)
    {}


    void removeEnabledElements(WorkFlow& workFlow)
    {
        std::vector<std::unique_ptr<SceneNode>>& elements = workFlow.setElements();

        auto result = elements.begin(), first = elements.begin();

        while (first != elements.end())
        {
            if (!(*first)->getEnable())
            {
              *result = std::move(*first);
              ++result;
            }
            ++first;
        }
        elements.erase(result, elements.end());
    }

    // Major function for process events.
    void UserInput::processEvents(std::vector<std::unique_ptr<WorkFlow>>& workFlows, std::vector<std::unique_ptr<Button>>& buttons, unsigned int& frameNumber)
    {
        sf::Event event;
        SceneNode* activeElement = checkActiveElements(*workFlows[frameNumber], buttons);

        if (mType == UserInput::MoveType)
            moveElements(*workFlows[frameNumber], sf::Mouse::getPosition(mWindow), activeElement);

        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                    mWindow.close();
            if (event.type == sf::Event::MouseButtonPressed && event.key.code == static_cast<unsigned int>(sf::Mouse::Left))
            {
                if (isMousePositionInArea(sf::Mouse::getPosition(mWindow), (*workFlows[frameNumber]).getRect(), true))
                    processInstruments(*workFlows[frameNumber], sf::Mouse::getPosition(mWindow), activeElement);
                else
                {
                    processButtons(workFlows, buttons, event);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == static_cast<unsigned int>(sf::Keyboard::Delete))
            {
                removeEnabledElements(*workFlows[frameNumber]);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == static_cast<unsigned int>(sf::Keyboard::A))
            {
                if (frameNumber != 0)
                    frameNumber -= 1;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == static_cast<unsigned int>(sf::Keyboard::D))
            {
                if (frameNumber != workFlows.size() - 1)
                    frameNumber += 1;
            }
        }
    }

    void UserInput::moveElements(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement)
    {
        if (activeElement != nullptr && activeElement->getNodeType() == SceneNode::Point)
        {
            Point* point = static_cast<Point*>(activeElement);
            Line* line { nullptr };
            std::vector<Line*> dependentLinesFirstPoint{}, dependentLinesSecondPoint{};

            for (auto& element : workFlow.setElements())
            {
                if (element->getNodeType() == SceneNode::Line)
                {
                    line = static_cast<Line*>(element.get());

                    if (line->getFirstPosition() == point->getPosition())
                        dependentLinesFirstPoint.push_back(line);
                    else if (line->getSecondPosition() == point->getPosition())
                        dependentLinesSecondPoint.push_back(line);
                }

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                point->setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
                for (auto line : dependentLinesFirstPoint)
                    line->setFirstPosition(point->getPosition());
                for (auto line : dependentLinesSecondPoint)
                    line->setSecondPosition(point->getPosition());
            }
        }
    }


    // Function for process every Instrument!!!!
    void UserInput::processSelectInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement)
    {
        if (activeElement != nullptr)
            activeElement->setEnable(!activeElement->getEnable());
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


    void UserInput::processInstruments(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement)
    {
        sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);

        switch (mType)
        {
            case SelectType:
                processSelectInstrument(workFlow, positionMouse, activeElement);
                break;

            case PointType:
                processPointInstrument(workFlow, positionMouse, activeElement);
                break;

            case LineType:
                processLineInstrument(workFlow, positionMouse, activeElement);
                break;

            case MoveType:
            case AddFrameType:
            case DeleteFrameType:
            case ExitType:
                break;
        }
    }

    void UserInput::processButtons(std::vector<std::unique_ptr<WorkFlow>>& workFlows,
                                   std::vector<std::unique_ptr<Button>>& buttons, sf::Event event)
    {
        sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);
        for (auto& button : buttons)
        {
            if (isMousePositionInArea(positionMouse, button->getRect(), false))
            {
                if (button->getAction() == AddFrameType)
                {
                    std::unique_ptr<WorkFlow> newWorkFlow{ new WorkFlow(mWindow) };
                    workFlows.push_back(std::move(newWorkFlow));
                }
                else if (static_cast<InstrumentType>(button->getAction()) == DeleteFrameType)
                {
                    //Добавить проверку на то что текущий кадр - не удаляемый.
                    if (workFlows.size() > 1)
                        workFlows.erase(workFlows.end() - 1, workFlows.end());
                }
                else if (static_cast<InstrumentType>(button->getAction()) == ExitType)
                {
                    mWindow.close();
                }
                else
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
