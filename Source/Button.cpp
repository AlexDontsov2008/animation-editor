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


        if (mIsEnable)
        {
            mBox.setEnable(true);
            mLabel.setEnable(true);
        }
        else
        {
            mBox.setEnable(false);
            mLabel.setEnable(false);
            if (mIsActive)
            {
                mBox.setActive(true);
                mLabel.setActive(true);
            }
            else
            {
                mBox.setActive(false);
                mLabel.setActive(false);
            }
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

    bool Button::getActive() const
    {
        return mIsActive;
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

    void Button::setLabelPosition(const sf::Vector2f& position)
    {
        mLabel.setPosition(position);
    }

    sf::Vector2f Button::getLabelPosition() const
    {
        return mLabel.getPosition();
    }
}


















