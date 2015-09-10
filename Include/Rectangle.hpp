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
        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            void                    setColor(const sf::Color& color);
            void                    init(float posX, float posY);

        private:
            sf::RectangleShape      mRectangle;
            sf::Color               mColor;
    };
}

#endif // _RECTANGLE_HPP_
