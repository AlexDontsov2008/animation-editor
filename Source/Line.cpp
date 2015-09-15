#include <Line.hpp>
#include <Utility.hpp>
#include <InitialParametrs.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

namespace Editor
{
    Line::Line(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos)
    : mLine()
    , mFirstPosition(firstPos)
    , mSecondPosition(secondPos)
    , mColor(InactiveColor)
    , mAngle(0.f)
    , mIsActive(false)
    , mIsEnable(false)
    {
        init();
    }

    Line::~Line()
    {}

    void Line::init()
    {
        sf::Vector2f vecLhs{ mSecondPosition - mFirstPosition };
        sf::Vector2f vecRhs{};

        float additAngle{ 0.f };

        if ((mFirstPosition.x > mSecondPosition.x &&  mFirstPosition.y < mSecondPosition.y) ||
            (mFirstPosition.x < mSecondPosition.x &&  mFirstPosition.y > mSecondPosition.y))
        {
            if (mFirstPosition.y > mSecondPosition.y)
                additAngle = rightAngle * 3.f;
            else
                additAngle = rightAngle;
            vecRhs = sf::Vector2f{ 0, mSecondPosition.y - mFirstPosition.y };
        }
        else
        {
            if (mFirstPosition.x > mSecondPosition.x)
                additAngle = rightAngle * 2.f;
            vecRhs = sf::Vector2f{ mSecondPosition.x - mFirstPosition.x, 0 };
        }

        float angle{};

        if (mFirstPosition.x == mSecondPosition.x)
            if (mFirstPosition.y > mSecondPosition.y)
                angle = -rightAngle;
            else
                angle = rightAngle;
        else
            angle = angleBetweenVectors(vecLhs, vecRhs);

        std::cout << "Angle: " << angle + additAngle << '\n';
        std::cout << "firstPosition: " << mFirstPosition.x  << ", " << mFirstPosition.y << '\n';
        std::cout << "secondPosition: " << mSecondPosition.x << ", " << mSecondPosition.y << '\n';
        std::cout << "Line lenght: " << vectorLenght(mSecondPosition - mFirstPosition) << '\n';
        mAngle = angle + additAngle;

        mLine.setSize(sf::Vector2f(vectorLenght(vecLhs), LineThickness));
        mLine.setPosition(mFirstPosition);
        mLine.setRotation(angle + additAngle);
        mLine.setFillColor(mColor);
    }

    void Line::update(sf::Time dt)
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

        mLine.setFillColor(mColor);
    }

    void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mLine, states);
    }

    sf::FloatRect Line::getRect() const
    {
        return mLine.getGlobalBounds();
    }


    bool Line::getActive() const
    {
        return mIsActive;
    }

    void Line::setActive(bool isActive)
    {
        mIsActive = isActive;
    }

    SceneNode::NodeType Line::getNodeType() const
    {
        return SceneNode::Line;
    }

    float Line::getAngle() const
    {
        return mAngle;
    }

    float Line::getLenght() const
    {
        return vectorLenght(mSecondPosition - mFirstPosition);
    }

    void Line::setEnable(bool isEnable)
    {
        mIsEnable = isEnable;
    }

    bool Line::getEnable() const
    {
        return mIsEnable;
    }
}
