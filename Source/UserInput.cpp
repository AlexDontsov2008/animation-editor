#include <UserInput.hpp>
#include <Utility.hpp>
#include <InitialParametrs.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <InputWindow.hpp>

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <fstream>

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
                    processButtons(workFlows, buttons, event, frameNumber);
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
            else if (event.type == sf::Event::KeyPressed && event.key.code == static_cast<unsigned int>(sf::Keyboard::Escape))
            {
                mWindow.close();
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

    void UserInput::processAddFrame(std::vector<std::unique_ptr<WorkFlow>>& workFlows)
    {
        std::unique_ptr<WorkFlow> newWorkFlow{ new WorkFlow(mWindow) };
        workFlows.push_back(std::move(newWorkFlow));
    }

    void UserInput::processDeleteFrame(std::vector<std::unique_ptr<WorkFlow>>& workFlows, unsigned int& frameNumber)
    {
        if (workFlows.size() > 1)
        {
            if (frameNumber == workFlows.size() - 1)
                frameNumber -= 1;

            workFlows.erase(workFlows.end() - 1, workFlows.end());
        }
    }

    void UserInput::processLoadInstrument(std::vector<std::unique_ptr<WorkFlow>>& workFlows, unsigned int& frameNumber)
    {
        InputWindow loadWindow(InputWindow::LoadWindow, mWindow, "Load Window", "Input file name for load:");
        loadWindow.run();

        if (loadWindow.getFileName().size() == 0)
            return;

        std::ifstream loadFile(loadWindow.getFileName(), std::ios_base::in);

        frameNumber = 0;
        workFlows.erase(workFlows.begin(), workFlows.end());

        unsigned int workFlowsSize{};
        loadFile >> workFlowsSize;

        for (unsigned int i = 0; i < workFlowsSize; ++i)
        {
            std::unique_ptr<WorkFlow> newWorkFlow { new WorkFlow(mWindow) };
            workFlows.push_back(std::move(newWorkFlow));

            unsigned int elementsSize{};
            loadFile >> elementsSize;
            for (unsigned int j = 0; j < elementsSize; ++j)
            {
                unsigned int elementType{};
                loadFile >> elementType;

                if (static_cast<SceneNode::NodeType>(elementType) == SceneNode::Point)
                {
                    sf::Vector2f position{};
                    loadFile >> position.x >> position.y;
                    workFlows[i]->addPoint(position);
                }
                else if (static_cast<SceneNode::NodeType>(elementType) == SceneNode::Line)
                {
                    sf::Vector2f firstPos{}, secondPos{};
                    loadFile >> firstPos.x >> firstPos.y >> secondPos.x >> secondPos.y;
                    workFlows[i]->addLine(firstPos, secondPos);
                }
            }
        }
    }

    void UserInput::processSaveInstrument(const std::vector<std::unique_ptr<WorkFlow>>& workFlows) const
    {
        InputWindow saveWindow(InputWindow::SaveWindow, mWindow, "Save Window", "Input file name for save:");
        saveWindow.run();

        if (saveWindow.getFileName().size() == 0)
            return;
        std::ofstream saveFile(saveWindow.getFileName(), std::ios_base::out);

        saveFile << workFlows.size() << '\n';

        for (unsigned int i = 0; i < workFlows.size(); ++i)
        {
            saveFile << workFlows[i]->setElements().size() << ' ';

            for (auto& element : workFlows[i]->setElements())
            {
                if (element->getNodeType() == SceneNode::Point)
                {
                    const Point* point { static_cast<const Point*>(element.get()) };
                    saveFile << 1 << ' ';
                    saveFile << point->getPosition().x << ' ' << point->getPosition().y << ' ';
                }
                else if (element->getNodeType() == SceneNode::Line)
                {
                    const Line* line { static_cast<const Line*>(element.get()) };
                    saveFile << 2 << ' ';
                    saveFile << line->getFirstPosition().x << ' ' << line->getFirstPosition().y << ' ';
                    saveFile << line->getSecondPosition().x << ' ' << line->getSecondPosition().y << ' ';
                }
            }
            saveFile << '\n';
        }

        saveFile.close();
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
            case LoadType:
            case SaveType:
            case ExitType:
                break;
        }
    }

    void UserInput::processButtons(std::vector<std::unique_ptr<WorkFlow>>& workFlows,
                                   std::vector<std::unique_ptr<Button>>& buttons, sf::Event event, unsigned int& frameNumber)
    {
        sf::Vector2i positionMouse = sf::Mouse::getPosition(mWindow);
        for (auto& button : buttons)
        {
            if (isMousePositionInArea(positionMouse, button->getRect(), false))
            {
                if (static_cast<InstrumentType>(button->getAction()) == AddFrameType)
                {
                    processAddFrame(workFlows);
                }
                else if (static_cast<InstrumentType>(button->getAction()) == DeleteFrameType)
                {
                    processDeleteFrame(workFlows, frameNumber);
                }
                else if (static_cast<InstrumentType>(button->getAction()) == LoadType)
                {
                    processLoadInstrument(workFlows, frameNumber);
                    button->setActive(false);
                    for (auto& button : buttons)
                        if (button->getEnable())
                        {
                            setInstrumentType(static_cast<InstrumentType>(button->getAction()));
                            break;
                        }
                }
                else if (static_cast<InstrumentType>(button->getAction()) == SaveType)
                {
                    processSaveInstrument(workFlows);
                    button->setActive(false);
                    for (auto& button : buttons)
                        if (button->getEnable())
                        {
                            setInstrumentType(static_cast<InstrumentType>(button->getAction()));
                            break;
                        }
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
