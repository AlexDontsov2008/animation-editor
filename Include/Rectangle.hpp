#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include <SceneNode.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

namespace sf
{
    class RectangleShape;
}

namespace Editor
{
    class Rectangle : public SceneNode
    {
        public:
                                    Rectangle(float width, float height, float posX, float posY);
            virtual                 ~Rectangle();

            virtual void            update(sf::Time dt) override;
            virtual sf::FloatRect   getRect() const override;

            virtual bool            getActive() const override;
            virtual void            setActive(bool isActive) override;

            virtual void            setEnable(bool isEnable) override;
            virtual bool            getEnable() const override;

        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            void                    init(float posX, float posY);

        private:
            sf::RectangleShape      mRectangle;
            sf::Color               mColor;

            bool                    mIsActive;
            bool                    mIsEnable;
    };
}

#endif // _RECTANGLE_HPP_
