#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <SceneNode.hpp>

#include <SFML/Graphics/CircleShape.hpp>

namespace Editor
{
    class Point : public SceneNode
    {
        public:
                                    Point(float posX, float posY);
            virtual                 ~Point();

            virtual void            update(sf::Time dt) override;

        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            virtual sf::FloatRect   getRect() const override;

        private:
            void                    setColor(const sf::Color& color);

        private:
            sf::CircleShape         mPoint;
            sf::Color               mColor;
    };
}

#endif // _POINT_HPP_
