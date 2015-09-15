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
    , mColor(ActiveColor)
    , mIsActive(true)
    , mIsEnable(false)
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
        if (mIsEnable)
        {
            mColor = EnableColor;
        }
        else
        {
            if (mIsActive)
                mColor = ActiveColor;
            else
                mColor = InactiveColor;
        }
        mPoint.setFillColor(mColor);
    }

    sf::FloatRect Point::getRect() const
    {
        return mPoint.getGlobalBounds();
    }

    bool Point::getActive() const
    {
        return mIsActive;
    }

    void Point::setActive(bool isActive)
    {
        mIsActive = isActive;
    }

    SceneNode::NodeType Point::getNodeType() const
    {
        return SceneNode::Point;
    }

    void Point::setEnable(bool isEnable)
    {
        mIsEnable = isEnable;
    }

    bool Point::getEnable() const
    {
        return mIsEnable;
    }

     sf::Vector2f Point::getPosition() const
     {
        return mPoint.getPosition();
     }

     void Point::setPosition(const sf::Vector2f& position)
     {
        mPoint.setPosition(position);
     }
}
