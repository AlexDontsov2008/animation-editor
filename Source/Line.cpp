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
    , mColor(sf::Color::Black)
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
                additAngle = 270.f;
            else
                additAngle = 90.f;
            vecRhs = sf::Vector2f{ 0, mSecondPosition.y - mFirstPosition.y };
        }
        else
        {
            if (mFirstPosition.x > mSecondPosition.x)
                additAngle = 180.f;
            vecRhs = sf::Vector2f{ mSecondPosition.x - mFirstPosition.x, 0 };
        }

        float angle{};

        if (mFirstPosition.x == mSecondPosition.x)
            if (mFirstPosition.y > mSecondPosition.y)
                angle = -90.f;
            else
                angle = 90.f;
        else
            angle = angleBetweenVectors(vecLhs, vecRhs);



        mLine.setSize(sf::Vector2f(vectorLenght(vecLhs), LineThickness));
        mLine.setPosition(mFirstPosition);
        mLine.setRotation(angle + additAngle);
        mLine.setFillColor(mColor);
    }

    void Line::update(sf::Time dt)
    {
        // ...
    }

    void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mLine, states);
    }

    sf::FloatRect Line::getRect() const
    {
        return mLine.getGlobalBounds();
    }

    void Line::setColor(const sf::Color& color)
    {
        mColor = std::move(color);
    }
}
