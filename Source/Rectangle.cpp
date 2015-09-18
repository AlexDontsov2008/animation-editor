#include <Rectangle.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Editor
{
    Rectangle::Rectangle(float width, float height, float posX, float posY)
    : mRectangle(sf::Vector2f(width, height))
    , mColor(InactiveColor)
    //, mIsActive(false)
    //, mIsEnable(false)
    {
        init(posX, posY);
    }

    Rectangle::~Rectangle()
    {}

    // Update Rectangle.
    void Rectangle::update(sf::Time dt)
    {
        if (SceneNode::getEnable())
        {
            mColor = ActiveColor;
        }
        else
        {
            if (SceneNode::getActive())
                mColor = ActiveColor;
            else
                mColor = InactiveColor;
        }
        mRectangle.setOutlineColor(mColor);
    }

    // Get Rectangle Area.
    sf::FloatRect Rectangle::getRect() const
    {
        return mRectangle.getGlobalBounds();
    }

    // Set Color & Position.
    void Rectangle::setColor(const sf::Color& color)
    {
        mColor = color;
    }

    void Rectangle::setPosition(const sf::Vector2f& position)
    {
        mRectangle.setPosition(position);
    }

    // Draw Rectangle.
    void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mRectangle, states);
    }

    // Helper initialization function.
    void Rectangle::init(float posX, float posY)
    {
        mRectangle.setPosition(posX, posY);
        mRectangle.setFillColor(boxColor);
        mRectangle.setOutlineThickness(borderSize);
        mRectangle.setOutlineColor(mColor);
    }





/*

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
*/

}
