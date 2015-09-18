#include <Rectangle.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Editor
{
    Rectangle::Rectangle(float width, float height, float posX, float posY)
    : mRectangle(sf::Vector2f(width, height))
    , mColor(InactiveColor)
    , mIsActive(false)
    , mIsEnable(false)
    {
        init(posX, posY);
    }

    Rectangle::~Rectangle()
    {}

    void Rectangle::init(float posX, float posY)
    {
        mRectangle.setPosition(posX, posY);
        mRectangle.setFillColor(boxColor);
        mRectangle.setOutlineThickness(borderSize);
        mRectangle.setOutlineColor(mColor);
    }

    void Rectangle::update(sf::Time dt)
    {
        if (mIsEnable)
        {
            mColor = ActiveColor;
        }
        else
        {
            if (mIsActive)
                mColor = ActiveColor;
            else
                mColor = InactiveColor;
        }
        mRectangle.setOutlineColor(mColor);
    }

    void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mRectangle, states);
    }

    sf::FloatRect Rectangle::getRect() const
    {
        return mRectangle.getGlobalBounds();
    }

    bool Rectangle::getActive() const
    {
        return mIsActive;
    }

    void Rectangle::setActive(bool isActive)
    {
        mIsActive = isActive;
    }

    void Rectangle::setEnable(bool isEnable)
    {
        mIsEnable = isEnable;
    }

    bool Rectangle::getEnable() const
    {
        return mIsEnable;
    }

    void Rectangle::setColor(const sf::Color& color)
    {
        mColor = color;
    }

    void Rectangle::setPosition(const sf::Vector2f& position)
    {
        mRectangle.setPosition(position);
    }
}
