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

            virtual void                update(sf::Time dt) override;

            //  Return instrument Type.
            unsigned int                getAction() const;

            void                        setActive(bool isActive);
            void                        setEnable(bool isEnable);

            bool                        getEnable() const;

            virtual sf::FloatRect       getRect() const override;


        protected:
            virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            // Get position and size of our drawing elements.

        private:
            Rectangle                       mBox;
            Label                           mLabel;
            const unsigned int              mInstrumentType;

            bool                            mIsActive;
            bool                            mIsEnable;
    };
}

#endif // _BUTTON_HPP_
