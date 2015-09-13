#include <Button.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

namespace Editor
{

    Button::Button(unsigned int instrumentType, const sf::Font& font, const std::string& label,
                   float posX, float posY, bool isEnable)
    : mBox { buttonSize, buttonSize, posX, posY }
    , mLabel { font, label, posX + 10.f, posY + 20.f }
    , mInstrumentType { instrumentType }
    , mIsActive { false }
    , mIsEnable { isEnable }
    {}

    Button::~Button()
    {}

    void Button::update(sf::Time dt)
    {
        if (mIsActive)
        {
            mBox.setBorderColor(sf::Color::White);
            mLabel.setColor(sf::Color::White);
        }
        else
        {
            mBox.setBorderColor(GrayColor);
            mLabel.setColor(GrayColor);
        }

        if (mIsEnable)
        {
            mLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
            mLabel.setColor(sf::Color::White);
            mBox.setBorderColor(sf::Color::White);
        }
        else
        {
            mLabel.setStyle(sf::Text::Regular);
        }

        mBox.update(dt);
        mLabel.update(dt);
    }

    unsigned int Button::getAction() const
    {
        return mInstrumentType;
    }

    void Button::setActive(bool isActive)
    {
        mIsActive = isActive;
    }

    void Button::setEnable(bool isEnable)
    {
        mIsEnable = isEnable;
    }

    bool Button::getEnable() const
    {
        return mIsEnable;
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mBox, states);
        target.draw(mLabel, states);
    }

    sf::FloatRect Button::getRect() const
    {
        return mBox.getRect();
    }
}


















