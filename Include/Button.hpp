#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include <SceneNode.hpp>
#include <Rectangle.hpp>
#include <Label.hpp>

namespace Editor
{
    class Button : public SceneNode
    {
        public:
                                        Button(unsigned int instrumentType, const sf::Font& font, const std::string& label,
                                               float posX, float posY, bool isEnable);
            virtual                     ~Button();

            // Update Button.
            virtual void                update(sf::Time dt) override;

            //  Return Button Instrument Type.
            unsigned int                getAction() const;

            // Get Button Area.
            virtual sf::FloatRect       getRect() const override;

            // Set & Get Label Position.
            void                        setLabelPosition(const sf::Vector2f& position);
            sf::Vector2f                getLabelPosition() const;


        protected:
            // Draw Button.
            virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            Rectangle                       mBox;
            Label                           mLabel;
            // Instrument Type.
            const unsigned int              mInstrumentType;
    };
}

#endif // _BUTTON_HPP_
