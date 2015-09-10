#include <Rectangle.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Editor
{
    Rectangle::Rectangle(float width, float height, float posX, float posY)
    : mRectangle(sf::Vector2f(width, height))
    , mColor(sf::Color::White)
    {
        init(posX, posY);
    }

    Rectangle::~Rectangle()
    {}

    void Rectangle::init(float posX, float posY)
    {
        mRectangle.setPosition(posX, posY);
        mRectangle.setOutlineThickness(borderSize);
        mRectangle.setOutlineColor(sf::Color::Black);
    }

    void Rectangle::update(sf::Time dt)
    {
        // ...
    }

    void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mRectangle, states);
    }

    sf::FloatRect Rectangle::getRect() const
    {
        return mRectangle.getGlobalBounds();
    }

    void Rectangle::setColor(const sf::Color& color)
    {
        mColor = std::move(color);
    }
}
