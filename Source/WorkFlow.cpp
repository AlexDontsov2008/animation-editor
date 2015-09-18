#include <WorkFlow.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <InitialParametrs.hpp>

#include <iostream>

namespace Editor
{
    WorkFlow::WorkFlow(sf::RenderWindow& window)
    : mElements{}
    , mWindow(window)
    , mWorkArea(mWindow.getSize().x - 125.f, mWindow.getSize().y - 100.f, workAreaPosX, workAreaPosY)
    {}

    WorkFlow::~WorkFlow()
    {}

    // Update WorkFlow
    void WorkFlow::update(sf::Time dt)
    {
        mWorkArea.update(dt);

        for (auto& element : mElements)
        {
            element->update(dt);
        }
    }

    // Draw WorkFlow
    void WorkFlow::draw() const
    {
        mWindow.draw(mWorkArea);

        for (auto& element : mElements)
            mWindow.draw(*element);
    }

    // Get WorkFLow Area
    sf::FloatRect WorkFlow::getRect() const
    {
        return mWorkArea.getRect();
    }

     // Add Point & Line in WorkFlow
     void WorkFlow::addPoint(const sf::Vector2f& position)
     {
        std::unique_ptr<SceneNode> newPoint{ new Point(position.x, position.y) };
        mElements.push_back(std::move(newPoint));
     }

     void WorkFlow::addLine(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos)
     {
        std::unique_ptr<SceneNode> newLine{ new Line(firstPos, secondPos) };
        mElements.push_back(std::move(newLine));
     }

     // Set Active.
     void WorkFlow::setActive(bool isActive)
     {
        mWorkArea.setActive(isActive);
     }

     // Set element from reference on elements.
     std::vector<std::unique_ptr<SceneNode>>& WorkFlow::setElements()
     {
        return mElements;
     }

}
