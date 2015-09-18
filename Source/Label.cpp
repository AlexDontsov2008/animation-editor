#include <Label.hpp>
#include <InitialParametrs.hpp>


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Editor
{
    Label::Label(const sf::Font& font, const std::string& text, float posX, float posY)
    : SceneNode{}
    , mText{}
    , mColor{ InactiveColor }
    {
        initText(font, text, posX, posY);
    }

    Label::~Label()
    {}

    // Update for Label.
    void Label::update(sf::Time dt)
    {
        if (SceneNode::getEnable())
        {
            mText.setStyle(sf::Text::Bold | sf::Text::Underlined);
            mColor = ActiveColor;
        }
        else
        {
            if (SceneNode::getActive())
                mColor = ActiveColor;
            else
                mColor = InactiveColor;

            mText.setStyle(sf::Text::Regular);
        }
        mText.setColor(mColor);
    }


    // Set & Get Label Position.
    void Label::setPosition(const sf::Vector2f& position)
    {
        mText.setPosition(position);
    }

    void Label::setPosition(float posX, float posY)
    {
        mText.setPosition(posX, posY);
    }

    sf::Vector2f Label::getPosition() const
    {
        return mText.getPosition();
    }

    // Set Text, Style, Color.
    void Label::setText(const std::string& text)
    {
        mText.setString(text);
    }

    void Label::setStyle(unsigned int style)
    {
        mText.setStyle(style);
    }

    void Label::setColor(const sf::Color& color)
    {
        mColor = color;
    }

    // Draw Label.
    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mText, states);
    }

    // Get position and size of our drawing elements.
    sf::FloatRect Label::getRect() const
    {
        return mText.getGlobalBounds();
    }

    // Helper Initial function
    void Label::initText(const sf::Font& font, const std::string& text, float posX, float posY)
    {
        mText.setFont(font);
        mText.setString(text);
        mText.setPosition(posX, posY);
        mText.setCharacterSize(characterSize);
        mText.setColor(mColor);
    }
}



