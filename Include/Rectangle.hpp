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

            // Update Rectangle.
            virtual void            update(sf::Time dt) override;
            // Get Rectangle Area.
            virtual sf::FloatRect   getRect() const override;

            // Set Color & Position.
            void                    setColor(const sf::Color& color);
            void                    setPosition(const sf::Vector2f& position);

        protected:
            // Draw Rectangle.
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            // Helper initialization function.
            void                    init(float posX, float posY);

        private:
            sf::RectangleShape      mRectangle;
            // Attributes.
            sf::Color               mColor;

            //bool                    mIsActive;
            //bool                    mIsEnable;
    };
}

#endif // _RECTANGLE_HPP_
