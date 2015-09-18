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
    : SceneNode{}
    , mLine{}
    , mFirstPosition{ firstPos }
    , mSecondPosition{ secondPos }
    , mAngle{ 0.f }
    , mColor{ InactiveColor }
    {
        init();
    }

    Line::~Line()
    {}

    // Update Line.
    void Line::update(sf::Time dt)
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

        mLine.setFillColor(mColor);
    }

    // Get Line Type.
    SceneNode::NodeType Line::getNodeType() const
    {
        return SceneNode::Line;
    }

    // Get Angle & Lenght.
    float Line::getAngle() const
    {
        return mAngle;
    }

    float Line::getLenght() const
    {
        return vectorLenght(mSecondPosition - mFirstPosition);
    }

    // Get First & Second Position.
    sf::Vector2f Line::getFirstPosition() const
    {
        return mFirstPosition;
    }

    sf::Vector2f Line::getSecondPosition() const
    {
        return mSecondPosition;
    }

    // Set First & Second Position.
    void Line::setFirstPosition(const sf::Vector2f& firstPosition)
    {
        mFirstPosition = firstPosition;
        EvalutionLineParametrs();
    }

    void Line::setSecondPosition(const sf::Vector2f& secondPosition)
    {
        mSecondPosition = secondPosition;
        EvalutionLineParametrs();
    }

    // Draw Line.
    void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mLine, states);
    }

    // get Line Area.
    sf::FloatRect Line::getRect() const
    {
        return mLine.getGlobalBounds();
    }

    // Helper initialization function.
    void Line::init()
    {
        EvalutionLineParametrs();
        mLine.setFillColor(mColor);
    }

    // Evalution geometry parametrs.
    void Line::EvalutionLineParametrs()
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

        // Set Angle.
        mAngle = angle + additAngle;

        mLine.setSize(sf::Vector2f(vectorLenght(vecLhs), LineThickness));
        mLine.setPosition(mFirstPosition);
        mLine.setRotation(angle + additAngle);
    }

}
