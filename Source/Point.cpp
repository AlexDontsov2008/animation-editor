#include <Point.hpp>
#include <Utility.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>


#include <iostream>

namespace Editor
{
    Point::~Point()
    {}

    Point::Point(float posX, float posY)
    : mPoint(pointSize)
    , mColor(sf::Color::Black)
    {
        setCenterOrigin(mPoint);
        mPoint.setFillColor(mColor);
        mPoint.setPosition(posX, posY);
    }

    void Point::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mPoint, states);
    }

    void Point::update(sf::Time dt)
    {
        // ...
    }

    sf::FloatRect Point::getRect() const
    {
        return mPoint.getGlobalBounds();
    }

    void Point::setColor(const sf::Color& color)
    {
        mColor = std::move(color);
    }
}
