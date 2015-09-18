#include <Button.hpp>
#include <InitialParametrs.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>

namespace Editor
{

    Button::Button(unsigned int instrumentType, const sf::Font& font, const std::string& label,
                   float posX, float posY, bool isEnable)
    : SceneNode{}
    , mBox { buttonSize, buttonSize, posX, posY }
    , mLabel { font, label, posX + 10.f, posY + 20.f }
    , mInstrumentType { instrumentType }
    {
        SceneNode::setEnable(isEnable);
    }

    Button::~Button()
    {}

    // Update Button.
    void Button::update(sf::Time dt)
    {
        if (SceneNode::getEnable())
        {
            mBox.setEnable(true);
            mLabel.setEnable(true);
        }
        else
        {
            mBox.setEnable(false);
            mLabel.setEnable(false);
            if (SceneNode::getActive())
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

    //  Return Button Instrument Type.
    unsigned int Button::getAction() const
    {
        return mInstrumentType;
    }

    // Get Button Area.
    sf::FloatRect Button::getRect() const
    {
        return mBox.getRect();
    }

    // Draw Button.
    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mBox, states);
        target.draw(mLabel, states);
    }

    // Set & Get Label Position.
    void Button::setLabelPosition(const sf::Vector2f& position)
    {
        mLabel.setPosition(position);
    }

    sf::Vector2f Button::getLabelPosition() const
    {
        return mLabel.getPosition();
    }

}


















