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
    : SceneNode{}
    , mPoint{ pointSize }
    , mColor{ ActiveColor }
    {
        setCenterOrigin(mPoint);
        mPoint.setFillColor(mColor);
        mPoint.setPosition(posX, posY);
    }

    // Update Point
    void Point::update(sf::Time dt)
    {
        if (SceneNode::getEnable())
        {
            mColor = EnableColor;
        }
        else
        {
            if (SceneNode::getActive())
                mColor = ActiveColor;
            else
                mColor = InactiveColor;
        }
        mPoint.setFillColor(mColor);
    }

    // Get Point Type.
    SceneNode::NodeType Point::getNodeType() const
    {
        return SceneNode::Point;
    }

    // Get & Set Position
    sf::Vector2f Point::getPosition() const
    {
        return mPoint.getPosition();
    }

    void Point::setPosition(const sf::Vector2f& position)
    {
        mPoint.setPosition(position);
    }

    // Draw Point.
    void Point::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mPoint, states);
    }


    // Get Point Area.
    sf::FloatRect Point::getRect() const
    {
        constexpr float offset { 15.f };
        sf::FloatRect rect = mPoint.getGlobalBounds();
        return sf::FloatRect(rect.left - offset, rect.top - offset, rect.width + offset * 2.f, rect.height + offset * 2.f);
    }

}
