#include <Label.hpp>
#include <InitialParametrs.hpp>


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Editor
{
    Label::Label(const sf::Font& font, const std::string& text, float posX, float posY)
    : mText{}
    , mColor{ GrayColor }
    {
        initText(font, text, posX, posY);
    }

    Label::~Label()
    {}

    void Label::update(sf::Time dt)
    {
        mText.setColor(mColor);
    }

    void Label::setText(const std::string& text)
    {
        mText.setString(text);
    }

    void Label::setPosition(const sf::Vector2f& position)
    {
        mText.setPosition(position);
    }

    void Label::setPosition(float posX, float posY)
    {
        mText.setPosition(posX, posY);
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mText, states);
    }

    sf::FloatRect Label::getRect() const
    {
        return mText.getGlobalBounds();
    }

    void Label::initText(const sf::Font& font, const std::string& text, float posX, float posY)
    {
        mText.setFont(font);
        mText.setString(text);
        mText.setPosition(posX, posY);
        mText.setCharacterSize(characterSize);
        mText.setColor(mColor);
    }


    void Label::setColor(const sf::Color& color)
    {
        mColor = color;
    }

    void Label::setStyle(unsigned int style)
    {
        mText.setStyle(style);
    }
}



