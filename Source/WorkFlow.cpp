#include <WorkFlow.hpp>
#include <Point.hpp>
#include <Line.hpp>
#include <InitialParametrs.hpp>

namespace Editor
{
    WorkFlow::WorkFlow(sf::RenderWindow& window)
    : mElements{}
    , mWindow(window)
    , mWorkArea(workAreaWidth, workAreaHeight, workAreaPosX, workAreaPosY)
    {}

    WorkFlow::~WorkFlow()
    {}

    void WorkFlow::update(sf::Time dt)
    {
        mWorkArea.update(dt);

        for (auto& element : mElements)
            element->update(dt);
    }

    void WorkFlow::draw() const
    {
        mWindow.draw(mWorkArea);

        for (auto& element : mElements)
            mWindow.draw(*element);
    }

    sf::FloatRect WorkFlow::getRect() const
    {
        return mWorkArea.getRect();
    }

     // Functions for add the Points and the Lines on the WorkArea.
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

     void WorkFlow::setBorderColor(const sf::Color& color)
     {
        mWorkArea.setBorderColor(color);
     }
}
